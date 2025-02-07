from google.protobuf.internal import containers as _containers
from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Ship(_message.Message):
    __slots__ = ("alignment", "name", "class_ship", "length", "size", "armed", "officers")
    class Alignment(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        ALLY: _ClassVar[Ship.Alignment]
        ENEMY: _ClassVar[Ship.Alignment]
    ALLY: Ship.Alignment
    ENEMY: Ship.Alignment
    class Class(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
        __slots__ = ()
        Corvette: _ClassVar[Ship.Class]
        Frigate: _ClassVar[Ship.Class]
        Cruiser: _ClassVar[Ship.Class]
        Destroyer: _ClassVar[Ship.Class]
        Carrier: _ClassVar[Ship.Class]
        Dreadnought: _ClassVar[Ship.Class]
    Corvette: Ship.Class
    Frigate: Ship.Class
    Cruiser: Ship.Class
    Destroyer: Ship.Class
    Carrier: Ship.Class
    Dreadnought: Ship.Class
    class Officer(_message.Message):
        __slots__ = ("first_name", "last_name", "rank")
        FIRST_NAME_FIELD_NUMBER: _ClassVar[int]
        LAST_NAME_FIELD_NUMBER: _ClassVar[int]
        RANK_FIELD_NUMBER: _ClassVar[int]
        first_name: str
        last_name: str
        rank: str
        def __init__(self, first_name: _Optional[str] = ..., last_name: _Optional[str] = ..., rank: _Optional[str] = ...) -> None: ...
    ALIGNMENT_FIELD_NUMBER: _ClassVar[int]
    NAME_FIELD_NUMBER: _ClassVar[int]
    CLASS_SHIP_FIELD_NUMBER: _ClassVar[int]
    LENGTH_FIELD_NUMBER: _ClassVar[int]
    SIZE_FIELD_NUMBER: _ClassVar[int]
    ARMED_FIELD_NUMBER: _ClassVar[int]
    OFFICERS_FIELD_NUMBER: _ClassVar[int]
    alignment: Ship.Alignment
    name: str
    class_ship: Ship.Class
    length: float
    size: int
    armed: bool
    officers: _containers.RepeatedCompositeFieldContainer[Ship.Officer]
    def __init__(self, alignment: _Optional[_Union[Ship.Alignment, str]] = ..., name: _Optional[str] = ..., class_ship: _Optional[_Union[Ship.Class, str]] = ..., length: _Optional[float] = ..., size: _Optional[int] = ..., armed: bool = ..., officers: _Optional[_Iterable[_Union[Ship.Officer, _Mapping]]] = ...) -> None: ...

class Coordinates(_message.Message):
    __slots__ = ("hours", "minutes", "seconds")
    HOURS_FIELD_NUMBER: _ClassVar[int]
    MINUTES_FIELD_NUMBER: _ClassVar[int]
    SECONDS_FIELD_NUMBER: _ClassVar[int]
    hours: int
    minutes: int
    seconds: float
    def __init__(self, hours: _Optional[int] = ..., minutes: _Optional[int] = ..., seconds: _Optional[float] = ...) -> None: ...
