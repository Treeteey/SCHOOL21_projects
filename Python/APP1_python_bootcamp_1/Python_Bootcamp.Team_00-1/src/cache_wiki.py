import requests
import json
import argparse
import logging
from urllib.parse import urljoin, quote
from collections import deque
from bs4 import BeautifulSoup
import unittest

logging.basicConfig(level=logging.INFO, format="%(message)s")

BASE_URL = "https://en.wikipedia.org/wiki/"

def fetch_page(page_title):
    url = urljoin(BASE_URL, quote(page_title))
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    else:
        logging.error(f"Failed to fetch {url} (status code {response.status_code})")
        return None

def extract_links(html):
    soup = BeautifulSoup(html, "html.parser")
    wiki_links = set()

    # Ищем See also
    see_also_heading = soup.find("span", id="See_also")
    see_also_section = None
    if see_also_heading:
        see_also_section = see_also_heading.find_parent("h2")

    # Извлекаем ссылки из основного текста(до See also)
    main_sections = []
    elements = soup.find_all(["p", "ul", "ol", "h2"])
    for elem in elements:
        # Доходим до See also и перестаем собирать текст
        if elem == see_also_section:
            break
        if elem.name in ["p", "ul", "ol"]:
            main_sections.append(elem)

    # Извлекаем ссылки из основного текста
    for section in main_sections:
        for link in section.find_all("a", href=True):
            href = link['href']
            # Проверяем, что ссылка ведет на статью wiki
            if href.startswith("/wiki/") and ":" not in href and "#" not in href:
                wiki_links.add(href.split("/wiki/")[1])

    # Извлекаем ссылки из See also
    if see_also_section:
        for sibling in see_also_section.find_next_siblings():
            if sibling.name == "h2":
                break
            for link in sibling.find_all("a", href=True):
                href = link['href']
                if href.startswith("/wiki/") and ":" not in href and "#" not in href:
                    wiki_links.add(href.split("/wiki/")[1])

    return wiki_links

def crawl_wikipedia(start_page, depth=3, max_pages=200):
    visited = set()
    graph = {}
    queue = deque([(start_page, 0)])

    while queue:
        current_page, current_depth = queue.popleft()
        if current_page in visited:
            continue

        visited.add(current_page)
        logging.info(f"Visiting: {current_page}")

        # Каждые 50 страниц сообщаем прогрессе(просто для наглядности)
        if len(visited) % 50 == 0:
            logging.info(f"Collected {len(visited)} unique pages so far.")

        html = fetch_page(current_page)
        if not html:
            continue

        links = extract_links(html)
        graph[current_page] = list(links)

        # Проверка, не достигли ли мы лимита
        if len(visited) >= max_pages:
            logging.warning("Maximum page limit reached ( > 1000 )!")
            break

        if current_depth < depth:
            for link in links:
                if link not in visited:
                    queue.append((link, current_depth + 1))

    return graph, visited

def save_graph(graph, filename="wiki.json"):
    with open(filename, "w", encoding='utf-8') as f:
        json.dump(graph, f, ensure_ascii=False, indent=4)
    logging.info(f"Graph saved to {filename}")


def main():
    parser = argparse.ArgumentParser(description="Wikipedia Crawler")
    parser.add_argument("-p", "--page", default="Python_(programming_language)", 
                        help="Starting Wikipedia page (default: Python_(programming_language))")
    parser.add_argument("-d", "--depth", type=int, default=3, 
                        help="Depth of crawling (default: 3)")
    args = parser.parse_args()

    graph, visited = crawl_wikipedia(args.page, args.depth)
    # Другая начальная страница по умолчанию
    if len(visited) < 20:
        logging.warning("Collected less than 20 pages. Trying a different start page: 'Mathematics'")
        graph, visited = crawl_wikipedia("Mathematics", args.depth)

    save_graph(graph)

if __name__ == "__main__":
    main()
    # python3 cache_wiki.py -p "Mathematics" -d 2
