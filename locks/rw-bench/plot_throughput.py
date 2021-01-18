# plot_throughput.py
# Plot throughput benchmark results.

import os
from typing import Tuple, List
import matplotlib.pyplot as plt

STD_FILENAME = "std.results"
TBB_FILENAME = "tbb.results"

PLOT_NAME = "throughput.png"

def load_data_for(filename: str) -> Tuple[List, List]:
  t1 = []
  t2 = []
  with open(filename, "r") as f:
    for line in f:
      line = line.strip().split(",")
      prop = float(line[1])
      data = (int(line[0]), int(line[2]), int(line[3]))
      if prop == 0.1:
        t1.append(data)
      elif prop == 0.5:
        t2.append(data)
      else:
        raise Exception()

  return (t1, t2)

def add_to_plot(data: List[Tuple], label: str, color: str, style: str):
  x = [d[0] for d in data]
  y = [d[1] for d in data]
  plt.plot(x, y, label=label, color=color, linestyle=style)

def main():
  if not os.path.exists(STD_FILENAME) or not os.path.exists(TBB_FILENAME):
    return

  # t1 refers to 0.1 writer proportion
  # t2 refers to 0.5 writer proportion
  (std_t1, std_t2) = load_data_for(STD_FILENAME)
  (tbb_t1, tbb_t2) = load_data_for(TBB_FILENAME)

  assert len(std_t1) == len(tbb_t1)
  assert len(std_t2) == len(tbb_t2)

  add_to_plot(std_t1, "std read-heavy", "blue", "-")
  add_to_plot(std_t2, "std even-split", "blue", "--")
  add_to_plot(tbb_t1, "tbb read-heavy", "orange", "-")
  add_to_plot(tbb_t2, "tbb even-split", "orange", "--")

  plt.xlabel("Worker Count")
  plt.ylabel("Average Benchmark Duration (ms)")
  plt.title("Reader/Writer Lock Throughput")
  plt.legend()

  plt.savefig(PLOT_NAME)

if __name__ == "__main__":
  main()