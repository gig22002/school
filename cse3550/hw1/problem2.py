#Group 4 Problem 2 -GG
from ecdsa import SigningKey
import hashlib
# from Crypto.Hash import RIPEMD160
from ripemd import ripemd160
import base58

# |STEP 1|
#secret key and public key
sk = SigningKey.generate()
pk = sk.verifying_key

#hash pk using sha256
hashobj = hashlib.sha256(pk.to_string())
digest = hashobj.digest()

#hash pk sha256 digest using RIPEMD-160
hashobj2 = ripemd160.new()
hashobj2.update(digest)
digest2 = hashobj2.digest()

payload = b'\x00'+digest2

# print(digest2.hex())
# print(digest2)
# print(payload)

#  |STEP 2|
h1 = hashlib.sha256(payload)
d1 = h1.digest()
h2 = hashlib.sha256(d1)
d2 = h2.digest()
#print(payload)
payload += d2[0:4]
#print(d2)
#print(payload)

encoded1 = base58.b58encode(payload)
code_string = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"
x = int.from_bytes(payload, "big")
encoded = ""
while(x>0):
    x, remainder = divmod(x, 58)
    encoded += code_string[remainder]


for i in payload[::-1]:
    if i != 0: break
    encoded += "0"

result = encoded[::-1]
#print(result)
#print(base58.b58encode(payload))
print(encoded1)
