// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "amount.h"

#include "tinyformat.h"

const std::string CURRENCY_UNIT = "LONG";

CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nSize)
{
    //if (nSize > 0)
    if (nSize > 1000) // XXX Это условие предотвращает волюнтаризм при установки fee 
        nSatoshisPerK = nFeePaid*1000/nSize;
    else
        nSatoshisPerK = 0;
    
    //nSatoshisPerK = 0; // палюбасу есть 1 лонг за килобайт ( Свыше 1к - 2 LONG, Свыше 2к - 3 LONG, ...)
    if (nSatoshisPerK < 1) nSatoshisPerK=1;
}

CAmount CFeeRate::GetFee(size_t nSize) const
{
    //CAmount nFee = nSatoshisPerK*nSize / 1000;
    CAmount nFee = nSatoshisPerK*nSize / 1001 + 1; // если nSatoshisPerK==3 - то 1 Мбайту соответствует макс 3*1000 LONG (1/3 награды); по 1000 байт - еще 1 LONG, 1001 байт уже 2 LONG
    
    
//CAmount nFee = 1;

//    if (nFee == 0 && nSatoshisPerK > 0)
//        nFee = nSatoshisPerK;

    return nFee; // >= 1 Всегда ( в конструкторах CFeeRate предусмотрено nSatoshisPerK > 0 всегда )
}

std::string CFeeRate::ToString() const
{
    //return strprintf("%d.%08d %s/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN, CURRENCY_UNIT);
    return strprintf("%d.%01d %s/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN, CURRENCY_UNIT);
}
