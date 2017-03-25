#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

namespace Entities
{
    enum Type
    {
        Ball,
        Fire,
        Flag,
        MakeSmall,
        MakeBig,
        JumpBoost,
        FlyBoost,
        SpeedBoost,
        Gate,
        Dimond,
        Crystal,
        Spike
    };
}

namespace Texture
{
    enum Id
    {
        Ball,
        Fire,
        Flag,
        MakeSmall,
        MakeBig,
        JumpBoost,
        FlyBoost,
        SpeedBoost,
        GateOpen,
        GateClosed,
        Dimond,
        CheckPoint,
        Crystal,
        Spike
    };
}

#endif // ENTITYTYPES_H
