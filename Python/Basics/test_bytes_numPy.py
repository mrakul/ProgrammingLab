import numpy as np

payload = b'ABCAA'

if len(payload) == 0:
    exit

counts = np.bincount(np.frombuffer(payload, dtype=np.uint8), minlength=256)

probabilities = counts / len(payload)
probabilities = probabilities[probabilities > 0]
log2array = np.log2(probabilities)
log2probsArray = probabilities * np.log2(probabilities)

entropy_val = -np.sum(probabilities * np.log2(probabilities))



square_entropy = np.nansum((1 - np.bincount(np.frombuffer(payload, dtype=np.uint8)) / len(payload)) * np.sqrt(np.bincount(np.frombuffer(payload, dtype=np.uint8)) / len(payload)))

print(square_entropy)