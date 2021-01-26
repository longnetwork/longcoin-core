# LONG NETWORK Core API (bitcoin-core-0.12.1 compatible). JSON-RPC 1.0

### Complete list of commands:

**== Addressindex ==**  
getaddressbalance  
getaddressdeltas  
getaddressmempool  
getaddresstxids  
getaddressutxos  

**== Blockchain ==**  
getbestblockhash  
getblock "hash" ( verbose )  
getblockchaininfo  
getblockcount  

getblockhash index  
getblockhashes timestamp  
getblockheader "hash" ( verbose )  
getchaintips  
getdifficulty  
getmempoolinfo  
getrawmempool ( verbose )  
getspentinfo  
gettxout "txid" n ( includemempool )  
gettxoutproof ["txid",...] ( blockhash )  
gettxoutsetinfo  
verifychain ( checklevel numblocks )  
verifytxoutproof "proof"  

**== Control ==**  
getinfo  
help ( "command" )  
stop  

**== Generating ==**  
generate numblocks  
getgenerate  
setgenerate generate ( genproclimit )  

**== Mining ==**  
getblocktemplate ( "jsonrequestobject" )  
getmininginfo  
getnetworkhashps ( blocks height )  
prioritisetransaction <txid> <priority delta> <fee delta>  
submitblock "hexdata" ( "jsonparametersobject" )  

**== Network ==**  
addnode "node" "add|remove|onetry"  
clearbanned  
disconnectnode "node"  
getaddednodeinfo dns ( "node" )  
getconnectioncount  
getnettotals  
getnetworkinfo  
getpeerinfo  
listbanned  
ping  
setban "ip(/netmask)" "add|remove" (bantime) (absolute)  

**== Rawtransactions ==**  
createrawdata "from" "to" "hexstring"  
createrawtransaction [{"txid":"id","vout":n},...] {"address":amount,"data":"hex",...} ( locktime )  
decoderawtransaction "hexstring"  
decodescript "hex"  
fundrawtransaction "hexstring" includeWatching  
getrawtransaction "txid" ( verbose )  
sendrawtransaction "hexstring" ( allowhighfees )  
signrawtransaction "hexstring" ( [{"txid":"id","vout":n,"scriptPubKey":"hex","redeemScript":"hex"},...] ["privatekey1",...] sighashtype )  

**== Util ==**  
createmultisig nrequired ["key",...]  
estimatefee nblocks  
estimatepriority nblocks  
estimatesmartfee nblocks  
estimatesmartpriority nblocks  
validateaddress "bitcoinaddress"  
verifymessage "bitcoinaddress" "signature" "message"  

**== Wallet ==**  
abandontransaction "txid"  
addmultisigaddress nrequired ["key",...] ( "account" )  
backupwallet "destination"  
dumpprivkey "bitcoinaddress"  
dumppubkey "bitcoinaddress"  
dumpwallet "filename"  
encryptwallet "passphrase"  
getaccount "bitcoinaddress"  
getaccountaddress "account"  
getaddressesbyaccount "account"  
getbalance ( "account" minconf includeWatchonly )  
gethexdata "txid"  
getnewaddress ( "account" )  
getrawchangeaddress  
getreceivedbyaccount "account" ( minconf )  
getreceivedbyaddress "bitcoinaddress" ( minconf )  
gettransaction "txid" ( includeWatchonly )  
getunconfirmedbalance  
getwalletinfo  
importaddress "address" ( "label" rescan p2sh )  
importprivkey "bitcoinprivkey" ( "label" rescan )  
importpubkey "pubkey" ( "label" rescan )  
importwallet "filename"  
keypoolrefill ( newsize )  
listaccounts ( minconf includeWatchonly)  
listaddressgroupings  
listlockunspent  
listreceivedbyaccount ( minconf includeempty includeWatchonly)  
listreceivedbyaddress ( minconf includeempty includeWatchonly)  
listsinceblock ( "blockhash" target-confirmations includeWatchonly)  
listtransactions ( "account" count from includeWatchonly)  
listunspent ( minconf maxconf  ["address",...] )  
lockunspent unlock [{"txid":"txid","vout":n},...]  
move "fromaccount" "toaccount" amount ( minconf "comment" )  
sendfrom "fromaccount" "tobitcoinaddress" amount ( minconf "comment" "comment-to" )  
sendhexdata "from" "to" "hexstring" ( "comment" )  
sendmany "fromaccount" {"address":amount,...} ( minconf "comment" ["address",...] )  
sendtoaddress "bitcoinaddress" amount ( "comment" "comment-to" subtractfeefromamount )  
setaccount "bitcoinaddress" "account"  
settxfee amount  
signmessage "bitcoinaddress" "message"  
storeaddress "another" ( "label" )  

_**Documentation for each command with examples built into the kernel. To view the documentation for a specific command, you must use the `help` command:**_  
-Or poll the running kernel daemon:  
```bash
longcoin-cli -conf=<path to longcoin.conf> help <command>
```
-Or in the debug console of the running wallet (ctrl+shift+c):  
```bash
help <command>
```

**Example:**  
`help getwalletinfo`  
**Output:**  
```javascript
getwalletinfo
Returns an object containing various wallet state info.

Result:
{
  "walletversion": xxxxx,     (numeric) the wallet version
  "balance": xxxxxxx,         (numeric) the total confirmed balance of the wallet in LONG
  "unconfirmed_balance": xxx, (numeric) the total unconfirmed balance of the wallet in LONG
  "immature_balance": xxxxxx, (numeric) the total immature balance of the wallet in LONG
  "txcount": xxxxxxx,         (numeric) the total number of transactions in the wallet
  "keypoololdest": xxxxxx,    (numeric) the timestamp (seconds since GMT epoch) of the oldest pre-generated key in the key pool
  "keypoolsize": xxxx,        (numeric) how many new keys are pre-generated
  "unlocked_until": ttt,      (numeric) the timestamp in seconds since epoch (midnight Jan 1 1970 GMT) that the wallet is unlocked for transfers, or 0 if the wallet is locked
  "paytxfee": x.xxxx,         (numeric) the transaction fee configuration, set in LONG/kB
}

Examples:
> longcoin-cli getwalletinfo 
> curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getwalletinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:8332/
```

