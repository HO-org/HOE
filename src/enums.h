#pragma once


typedef enum CallbackType {
        READY = 0,
        UPDATE,
        RENDER,
        COLLISION,
        READYUPDATE,
        READYRENDER,
        READYCOLLISION,
        READYUPDATERENDER,
        READYUPDATECOLLISION,
        UPDATERENDER,
        UPDATECOLLISION,
        NOCALLBACK
    } CallbackType;