from datasets import load_dataset
import torch

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
data_files = {"train": "../data/train.csv", "validate": "../data/validate.csv"}

dataset = load_dataset(
    "institutional/institutional-books-1.0",
    revision="main",
    data_files=data_files,
    split="train",
)
