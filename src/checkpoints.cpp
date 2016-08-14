// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
            ( 0,  uint256("0x00000d498e37f3531ed93b66128f562dd38faf46974daee738b89eaae384a745") ) // Params().HashGenesisBlock())
            ( 1,  uint256("0x000004b58f31d33ae05e7edcd9c76006dcd34a28274f1fd1e1895dfcd621dc1e") )
            ( 900,  uint256("0x00000d45345bce8ba109966132d020793e7f6dc3dc6c8e5d061e02a32a808a81") )
            ( 5000,  uint256("0x71b6479e55eb8020480544981b346ecaf3569e705485cdc1912643c50cbe6619") )
            ( 10000,  uint256("0x000001c92c3d092482c36272310e9e7eba9e09f0194d293a39be143a30940a9a") )
            ( 20000,  uint256("0x2856d047dc5099bf5dfa354c24987a70b06bcd2bd041d8e97e5a433b40adb42b") )
            ( 30000,  uint256("0xd554a0072d4e2c4b858021dc3a7af07a4ff732bf71532645ce1c0cd30173f016") )
            ( 40000,  uint256("0x5be2bc259a6b20b0cf8c1c34bc03488e7d17b78e1ab8a7ac55357d645b7f7f76") )
            ( 50000,  uint256("0xdbffa23fb885b4040a48761de9fd76490a9924873326743d75ce8f08548fcde5") )
 /*     ( 60000,  uint256("0xef24a387dd6ba7fb9aa9c7edfc3fbfc3ccdd2406a1be8e24426eca41d19996d5") )
        ( 70000,  uint256("0xe6369ee665c6a4a00bac6fa707123887144a5855eb45cd7a1d164d27707a0e93") )
        ( 80000,  uint256("0x09b00f6efb3a94de1c58ad578d19c1d7d74b0a6e101f750478ae987a713c6143") )
        ( 90000,  uint256("0xbf7040b9157c4611265371b9b2d6250aa956c6c237c4222a70a93dad800ff7d9") )
        ( 100000, uint256("0x6768cdd2f7630b68d61bf82cdd133bed2e7c858aba7e58190ed541c707a82daf") )
        ( 110000, uint256("0xb582e172d169bc67adc79969c35851c9156b5a4ad57c3fb3647a3aed20c8ba51") )
        ( 120000, uint256("0xa4d5f4a951f2cb5f6beafcbf8490a4645ac7585f0389d730613d4e22a96590eb") )
        ( 130000, uint256("0xa51baaa8f0b5f35217479b4defd61f3ae18b5792033a723dd9bd802a78b48803") )
        ( 140000, uint256("0x179d20535a7cd197c9e79258aac98c193cffa0265ce2ec0ea8c71b2e7f1fc021") )
        ( 150000, uint256("0x5d78df4991a4f10879452680f4643c27ef603f3928ff0d6ac05b5f14e5182029") )
        ( 160000, uint256("0x2fecb1a06ec490922e500b653948923952a6241c478df754f894c3b66d95f234") )
        ( 170000, uint256("0x04aa633b0850a8ca967ab40436c3068c385000d2ad08def923c8cb1328affa49") )
        ( 180000, uint256("0x79f341c763f658833280f62e70d04ecdb4c8e22181dca4e423692dd6d2dc7c92") )
        ( 190000, uint256("0x19ff2576455a3256772efebc1d88c356ebe18c74005454880cf46fab50c627c7") )
        ( 200000, uint256("0xd9af28b1b16e20aff1bdafdbdeaa793af8475681e3c2b5b6ad13d28ae6da6b1e") )
        ( 245000, uint256("0xe075bf70c40a7c18cc7bf305b2922ca690a13473b6edf05b4a452a85539fe50c") )
        ( 250000, uint256("0x19a6a7fe4d2b6db91160a2b0e46bf5045e8b9f3c3e15016c48e77657cadaa5b8") )
        ( 300000, uint256("0xb7f4f3b08a10eb7045cdfc7070856530dfae6fa4630b983b2922be80dfd91f3e") )
        ( 350000, uint256("0x27e5167742fa86a107a7823eac252985199fcf4e0aa8fa438af3d9b0e609824f") )
        ( 400000, uint256("0x25d4b6ab78cf3648b5b86bbcfe5f975a02ae1006231f84a19f9af598a0ae7557") )
        ( 500000, uint256("0xa85a7561b73c2549bf909fb3b51b384d915b8f83c321fc4977b201d4be2a8a0b") )
        ( 590000, uint256("0x680d2a36efdf4989c82cf144c36ba7ca398d0ba557f00ae51de07cba649823b4") )
        ( 765000, uint256("0x40fd13a50feaca5a54dd7834b97b2ddce2fee85b42a95ea2079edd3a81f22857") )
   */
         ;

    // TestNet has no checkpoints
    MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end())
            return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    CBlockThinIndex* GetLastCheckpoint(const std::map<uint256, CBlockThinIndex*>& mapBlockThinIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockThinIndex*>::const_iterator t = mapBlockThinIndex.find(hash);
            if (t != mapBlockThinIndex.end())
                return t->second;
        }
        return NULL;
    }


    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Automatically select a suitable sync-checkpoint - Thin mode
    const CBlockThinIndex* AutoSelectSyncThinCheckpoint()
    {
        const CBlockThinIndex *pindex = pindexBestHeader;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        if(nNodeMode == NT_FULL)
        {
            const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

            if (nHeight <= pindexSync->nHeight)
                return false;
        }
        else {
            const CBlockThinIndex *pindexSync = AutoSelectSyncThinCheckpoint();

            if (nHeight <= pindexSync->nHeight)
                return false;
        }
        return true;
    }
}
