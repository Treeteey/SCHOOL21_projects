# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc
import warnings

import ship_pb2 as ship__pb2

GRPC_GENERATED_VERSION = '1.69.0'
GRPC_VERSION = grpc.__version__
_version_not_supported = False

try:
    from grpc._utilities import first_version_is_lower
    _version_not_supported = first_version_is_lower(GRPC_VERSION, GRPC_GENERATED_VERSION)
except ImportError:
    _version_not_supported = True

if _version_not_supported:
    raise RuntimeError(
        f'The grpc package installed is at version {GRPC_VERSION},'
        + f' but the generated code in ship_pb2_grpc.py depends on'
        + f' grpcio>={GRPC_GENERATED_VERSION}.'
        + f' Please upgrade your grpc module to grpcio>={GRPC_GENERATED_VERSION}'
        + f' or downgrade your generated code using grpcio-tools<={GRPC_VERSION}.'
    )


class ServerResponceStub(object):
    """опрелелить тип передаваемых сообщений от клиента к серверу
    """

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.RouteChat = channel.stream_stream(
                '/ship.ServerResponce/RouteChat',
                request_serializer=ship__pb2.Coordinates.SerializeToString,
                response_deserializer=ship__pb2.Ship.FromString,
                _registered_method=True)


class ServerResponceServicer(object):
    """опрелелить тип передаваемых сообщений от клиента к серверу
    """

    def RouteChat(self, request_iterator, context):
        """when client send sequence of messages (2 Coordinates) and wait till
        server returns responce as sequence Ship messages (1-10 messages/ random number)
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ServerResponceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'RouteChat': grpc.stream_stream_rpc_method_handler(
                    servicer.RouteChat,
                    request_deserializer=ship__pb2.Coordinates.FromString,
                    response_serializer=ship__pb2.Ship.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'ship.ServerResponce', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))
    server.add_registered_method_handlers('ship.ServerResponce', rpc_method_handlers)


 # This class is part of an EXPERIMENTAL API.
class ServerResponce(object):
    """опрелелить тип передаваемых сообщений от клиента к серверу
    """

    @staticmethod
    def RouteChat(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(
            request_iterator,
            target,
            '/ship.ServerResponce/RouteChat',
            ship__pb2.Coordinates.SerializeToString,
            ship__pb2.Ship.FromString,
            options,
            channel_credentials,
            insecure,
            call_credentials,
            compression,
            wait_for_ready,
            timeout,
            metadata,
            _registered_method=True)
