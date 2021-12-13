#pragma once

#include "../Misc/CUserCmd.hpp"

#define MULTIPLAYER_BACKUP 150

class bf_write;
class bf_read;

class CInput
{
public:
	std::byte			pad0[0xC];				//0x0000
    bool				bTrackIRAvailable;		//0x000C
    bool				bMouseInitialized;		//0x000D
    bool				bMouseActive;			//0x000E
    std::byte			pad1[0xB2];				//0x000F
    bool				m_fCameraInThirdPerson;	//0x00C1
    std::byte			pad2[0x2];				//0x00C2
    QAngle				m_vecCameraOffset;		//0x00C4
    std::byte			pad3[0x38];				//0x00D0
    CUserCmd* m_pCommands;				//0x0108
    CVerifiedUserCmd* pVerifiedCommands;		//0x010C

    CUserCmd* GetUserCmd(const int nSequenceNumber) const
    {
        return &m_pCommands[nSequenceNumber % MULTIPLAYER_BACKUP];
    }

    CVerifiedUserCmd* GetVerifiedCmd(const int nSequenceNumber) const
    {
        return &pVerifiedCommands[nSequenceNumber % MULTIPLAYER_BACKUP];
    }

    CUserCmd* GetUserCmd(int slot, int sequence_number)
    {
        return &m_pCommands[slot, sequence_number % MULTIPLAYER_BACKUP];
    }
};
