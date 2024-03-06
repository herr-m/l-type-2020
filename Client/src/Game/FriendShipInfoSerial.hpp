#ifndef _FRIENDSHIPINFOSERIAL_H_
#define _FRIENDSHIPINFOSERIAL_H_

struct FriendShipInfoSerial final {
    const unsigned hp, numLives, playerID;
    constexpr FriendShipInfoSerial(unsigned hp, unsigned numLives, unsigned playerID) noexcept :
        hp(hp), numLives(numLives), playerID(playerID) {}
};

#endif
