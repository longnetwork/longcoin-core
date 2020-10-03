# LONG NETWORK Core — Cryptographic decentralized network on an open source blockchain (based on bitcoin-core-0.12.1)

LONG NETWORK works on the principle of encryption of all outgoing messages. All messages automatically fall into a single blockchain,
accessible to all network members, and the fact that messages appear on the blockchain is “seen” by everyone. But! Even the sender
cannot determine which computer will ultimately “read” the message, since only the addressee who owns the secret private key associated
with the recipient’s address can “read” the message.
Unlike traditional crypto messengers and networks, it is impossible to establish the very fact of “contact” of the sender and the recipient,
which is the most compromising factor and makes it easy to decrypt messages by striking devices on the head.
The system uses addresses similar to Bitcoin network addresses, which can be created locally by the user in unlimited quantities.
https://longnetwork.github.io/


# Features

* Coin name: LONG COIN
* Coin ticker: LONG (LNG)
* Hash algorithm: SHA-256
* Message Encryption Algorithm: ecdh and aes cbc
* Coin Type: POW
* Block time: 2 minutes
* Premine: 0
* Mined Blocks confirmation: 30 blocks
* Transactions confirmation: 6 blocks
* Block reward: 10 000 LONG
* Fixed fee: 1 LONG/Кб
*  - Short SMS — 1 LONG
*  - Standard financial transactions — 1 LONG
*  - The limit on the amount of data transaction is 64kB (max fee is 64 LONG)
* Multicast transactions with simultaneous transmission of coins and messages

Build Process
===========================================================================================================================================

* For Build see bash script https://github.com/longnetwork/LONGNETWORK/blob/master/build.sh
and also a video tutorial https://youtu.be/H5FkmPRJiEo
* For specific steps for cross-building see https://github.com/longnetwork/LONGNETWORK/blob/master/crossbuild.txt
(customized cross-build tools are included in the repository!)

Startup Notes
===========================================================================================================================================

The longcoin-daemon and GUI-wallet by default looks for the `longcoin.conf` configuration file in the current launch directory 
(not in system default directory). If you need a specific location for the configuration and / or data directory with the wallet.dat and blocks, 
then specify the full paths at startup: 
```bash
longcoind -conf=<path to longcoin.conf> -datadir=<path to data dir>
longcoin-qt -conf=<path to longcoin.conf> -datadir=<path to data dir>
```
The data directory can also be specified in the configuration file with the full path or relative to the current launch directory:
```bash
datadir=<path to data dir>
```
(see debug.log after start for configuration and data directory search paths)

The current recommended configuration is here: https://github.com/longnetwork/LONGNETWORK/blob/master/contrib/longcoinX.XX-lin/longcoin.conf

## Attention!
For mining-pools, exchanges, explorers and other network services using longcoin, you can disable the creation of a PUBLIC account when you first start the wallet:
`-disablepublic` in command line or `disablepublic=1` in `longcoin.conf`
This reduces the use of VDS memory and prevents the processing of spam of PUBLIC messages that is unnecessary for mining-pools or others.
PUBLIC does not contain money transactions and if you do not need to read the public correspondence - it can be disabled.
In the future, you can always connect to the PUBLIC by importing the official private key of the PUBLIC address 1GztQxGTKdEFhctBhR38wR8skjqkd4Cqt8 :
```bash
longcoin-cli importprivkey KwSXQL9F9ohW6TmZYWiNmx3z9Bz8x6vbZ6rVvWAPHS4wtcwSoo8W "PUBLIC"
```
Core API
===========================================================================================================================================
https://github.com/longnetwork/LONGNETWORK/blob/master/coreAPI.md

## The dragon is coming...  https://longnetwork.github.io/community.html


