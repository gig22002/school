import hashlib
import time

def both_sha256(data):
    first = hashlib.sha256(data).digest()
    second = hashlib.sha256(first).digest()
    return second

def counting_zeros(bytes):
    binary = ""
    for i in bytes:
        binary += format(i, "08b") #convert the single byte to 8-bit binary string
        
    count = 0
    for i in binary:
        if i == "0":
            count += 1
        else:
            break
    return count

def mine(header, difficulty):
    nonce = 0
    start_time = time.time()
    
    while True:
        message = f"{header}{nonce}".encode()
        result = both_sha256(message)
        
        if counting_zeros(result) >= difficulty: #must have at least this many leading 0s
            end_time = time.time()
            total = end_time - start_time
            return nonce, total
        
        nonce += 1
        
if __name__ == "__main__":
    difficulty = [2, 4, 8]
    
    for i in difficulty:
        print(f"\nLeading zeros: {i}")
        nonce, total = mine("header", i)
        print(f"Nonces: {nonce}")
        print(f"Time: {total:.8f} seconds")