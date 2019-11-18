// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_PARAMS_H
#define BITCOIN_CONSENSUS_PARAMS_H

#include "uint256.h"
#include <map>
#include <string>

namespace Consensus {

enum DeploymentPos
{
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_CSV, // Deployment of BIP68, BIP112, and BIP113.
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    /** Бит позиции для выбора конкретного бит в nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in the past */
    /** Запустите MedianTime для подтверждения свертывания битов версии. Может быть дата в прошлом */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    /** Тайм-аут / истечение срока действия MedianTime для попытки развертывания. */
    int64_t nTimeout;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /** Used to check majorities for block version upgrade */
    int nMajorityEnforceBlockUpgrade;
    int nMajorityRejectBlockOutdated;
    int nMajorityWindow;
    /** Block height and hash at which BIP34 becomes active */
    int BIP34Height;
    uint256 BIP34Hash;
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks in a retargetting period,
     * (nPowTargetTimespan / nPowTargetSpacing) which is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    
    int64_t nPowTargetSpacing0;
    int64_t nPowTargetTimespan0;

int nHeight1;
    int64_t nPowTargetSpacing1;
    int64_t nPowTargetTimespan1;
int nHeight2;
    int64_t nPowTargetSpacing2;
    int64_t nPowTargetTimespan2;    
    
    int64_t DifficultyAdjustmentInterval (int block) const {
         if (block >= nHeight2 ) return nPowTargetTimespan2 / nPowTargetSpacing2;
         if (block >= nHeight1 ) return nPowTargetTimespan1 / nPowTargetSpacing1;
         if (block >= 0 ) return nPowTargetTimespan0 / nPowTargetSpacing0;
         return nPowTargetTimespan2 / nPowTargetSpacing2; // default - last rules
    }
    int64_t PowTargetSpacing(int block) const {
        if (block >= nHeight2 ) return nPowTargetSpacing2;
        if (block >= nHeight1 ) return nPowTargetSpacing1;
        if( block >= 0) return nPowTargetSpacing0;
        return nPowTargetSpacing2; // default - last rules
    }
    int64_t PowTargetTimespan(int block) const {
        if (block >= nHeight2 ) return nPowTargetTimespan2;
        if (block >= nHeight1 ) return nPowTargetTimespan1;
        if( block >= 0) return nPowTargetTimespan0;
        return nPowTargetTimespan2; // default - last rules
    } 
};
} // namespace Consensus

#endif // BITCOIN_CONSENSUS_PARAMS_H
