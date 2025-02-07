#A WSGI server (meaning WSGI compliant) only receives the request
# from the client, pass it to the application and then send the 
# response returned by the application to the client. It does nothing else

from wsgiref.simple_server import make_server


species = {
    'Cyberman': 'John Lumic',
    'Dalek': 'Davros',
    'Judoon': 'Shadow Proclamation Convention 15 Enforcer',
    'Human': 'Leonardo da Vinci',
    'Ood': 'Klineman Halpen',
    'Silence': 'Tasha Lem',
    'Slitheen': 'Coca-Cola salesman',
    'Sontaran': 'General Staal',
    'Time Lord': 'Rassilon',
    'Weeping Angel': 'The Division Representative',
    'Zygon': 'Broton'
}

# environ points to a dictionary containing CGI like environment
# variables which is populated by the server for each
# received request from the client

# start_response is a callback function supplied by the server
# which takes the HTTP status and headers as arguments
def application(environ, start_response):

    # QUERY_STRING - переменная в которой хранится строка с параметрами запроса
    query_string = environ['QUERY_STRING']
    
    # print(name)
    if query_string and query_string.startswith('species='):
        name = query_string.split('=')[1].replace('%20', ' ')
        if name in species:
            response_body = '{"credentials": "%s"}' % species[name]
            # HTTP response code and message
            status = '200 OK'
        else:
            response_body = '{"credentials": "Unknown"}'
            status = '404 Not Found'
    else:
        response_body = '{"credentials": "Unknown"}'
        status = '404 Not Found'
    
    # HTTP headers expected by the client
    # They must be wrapped as a list of tupled pairs:
    # [(Header name, Header value)].
    response_headers = [
        ('Content-Type', 'text/plain'),
        ('Content-Length', str(len(response_body)))
    ]



    # Send them to the server using the supplied function
    start_response(status, response_headers)

    return [response_body.encode('utf-8')]


def run_server():
    # Instantiate the server
    httpd = make_server (
        'localhost', # The host name
        8888, # A port number where to wait for the request
        application # The application object name, in this case a function
    )

    # Wait for a single request, serve it and quit
    httpd.handle_request()
    # httpd.serve_forever()

# When the request method is GET the form variables will be sent 
# in the URL in the part called query string, that is, everything after the ?



import unittest

class TestApplicationFunction(unittest.TestCase):

    def test_application(self):
        cases = [
            {'species=Time%20Lord' : 'Rassilon'},
            {'species=Unknown' : 'Unknown'},
            {'species=' : 'Unknown'},
            {'invalid=Zygon' : 'Unknown'},
            {'' : 'Unknown'}
        ]

        for case in cases:
            with self.subTest(case=case):
                environ = {
                    'QUERY_STRING': list(case.keys())[0],
                    'REQUEST_METHOD': 'GET'
                }
                start_response = lambda status, headers: None
                response = application(environ, start_response)
                self.assertEqual(response[0].decode('utf-8'), '{"credentials": "%s"}' % list(case.values())[0])

if __name__ == '__main__':
    # unittest.main()
    run_server()