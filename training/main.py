from datasets import load_dataset
import torch

# Replace with C++ pybinding for non-GIL multithreading
import tokenizer

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
data_files = {"train": "../data/train.csv", "validate": "../data/validate.csv"}

dataset = load_dataset(
    "institutional/institutional-books-1.0",
    revision="main",
    data_files=data_files,
    split="train",
)

model_path = "m.model"
tok = tokenizer.Tokenizer(model_path)  # type: ignore

sample_text = "Hello world, this is a test!"
print(f"Original text: {sample_text}")

token_ids = tok.encode(sample_text)
print(f"Token IDs: {token_ids}")

decoded_text = tok.decode(token_ids)
print(f"Decoded text: {decoded_text}")

# file_content = tok.readFile("some_file.txt")
