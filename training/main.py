from datasets import load_dataset
import torch
import time

# Replace with C++ pybinding for non-GIL multithreading
import tokenizer

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
data_files = {"train": "../data/train.csv", "validate": "../data/validate.csv"}

# dataset = load_dataset(
#     "institutional/institutional-books-1.0",
#     revision="main",
#     data_files=data_files,
#     split="train",
# )
start_time = time.time()

model_path = "m.model"
tok = tokenizer.Tokenizer(model_path)  # type: ignore
file_content = tok.readFile("../data/tiny_shakespere.txt")


token_ids = tok.encode(file_content)
print(f"Token IDs: {token_ids}")

decoded_text = tok.decode(token_ids)
print(f"Decoded text: {decoded_text}")

end_time = time.time()
print(f"Total time: {end_time - start_time:.4f} seconds")
