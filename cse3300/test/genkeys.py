from Cryptodome.PublicKey import RSA

key = RSA.generate(2048)
pwd = b'test'
with open("sk.pem", "wb") as f:
    data = key.export_key(passphrase=pwd,
                          pkcs=8,
                          protection='PBKDF2WithHMAC-SHA512AndAES256-CBC',
                          prot_params={'iteration_count':131072})
    f.write(data)

with open("sk.pem", "rb") as f:
    data = f.read()
    key = RSA.import_key(data, pwd)

with open("pk.pem", "wb") as f:
    data = key.public_key().export_key()
    f.write(data)
