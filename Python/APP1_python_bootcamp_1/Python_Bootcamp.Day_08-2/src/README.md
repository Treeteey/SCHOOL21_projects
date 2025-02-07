## EX00

1) `py fight.py`

## EX01

1) `pip intstall httpx`
2) `pip install uuid`
3) `pip install pydantic`
4) `pip install fastapi`
5) `py server.py`
6) `py crawl.py https://docs-python.ru/packages/freimvork-fastapi/model-otveta/ https://metanit.com/go/tutorial/2.2.php  https://whatisthisdog.org`


## EX02


1) `redis-server`  in first terminal
2) `py server_cached.py` - in second terminal
   In third terminal:
3) `py crawl.py "https://yandex.ru/search/?text=redis-cli+команды&lr=43&clid=2270485&win=616&src=suggest_B" "https://habr.com/ru/articles/204354/"`
4) `py crawl.py https://docs-python.ru/packages/freimvork-fastapi/model-otveta/ https://metanit.com/go/tutorial/2.2.php  https://whatisthisdog.org`
5) `py crawl.py "https://yandex.ru/search/?text=wiki&lr=43&clid=2270485&win=616"`
6) Если не получается проверить какой-либо url, то ему присваивается код ошибки 599!
7) При повторной отправке url, появится сообщение **URL {...} is cached***


Чтобы узнать метрики из Redis клиента, в терминале надо запустить клиентскую программу:
1) `redis-cli`
2) `keys *` - покажет закешированные данные
3) `get "https://metanit.com/go/tutorial/2.2.php"`  - покажет сохраненный код ответа
4) `get domain:metanit.com` - покажет сколько раз обращались к домену
   