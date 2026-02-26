#Group 4 Problem 1 -GG
from ecdsa import SigningKey
import hashlib

msg = b'CSE-3550-5500'

#secret key and public key
sk = SigningKey.generate()
pk = sk.verifying_key

#hash message
hashobj = hashlib.sha256(msg)
digest = hashobj.digest()

# print(hashobj.hexdigest())

#sign
sig = sk.sign(digest)

#check
msgVer = b'CSE-3550-5500'
hashobjVer = hashlib.sha256(msgVer)
digestVer = hashobj.digest()
assert pk.verify(sig, digestVer)
print(pk.verify(sig, digestVer))
