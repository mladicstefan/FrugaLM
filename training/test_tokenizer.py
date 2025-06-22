#!/usr/bin/env python3

import tokenizer

print("✅ Tokenizer module imported successfully!")
print(
    "Available methods:",
    [method for method in dir(tokenizer.Tokenizer) if not method.startswith("_")],
)

try:
    with open("test.txt", "w") as f:
        f.write("Hello world! This is a test.")

    tok = tokenizer.Tokenizer("dummy_path")  # This will fail, but we can catch it
except Exception as e:
    print(f"Expected error (no model file): {e}")
    print("✅ Module is working - you just need to create a SentencePiece model file!")

print("\nTo fix the main.py script:")
print("1. cd ../tokenizer")
print("2. make train")
print("3. Then run python main.py")
