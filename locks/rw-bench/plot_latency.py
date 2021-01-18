# plot_latency.py
# Plot latency benchmark results.

import os
from typing import Tuple, List
import matplotlib.pyplot as plt

STD_FILENAME = "std.results"
TBB_FILENAME = "tbb.results"

READ_HEAVY_NAME = "latency_read_heavy.png"
EQUAL_LOAD_NAME = "latency_equal_load.png"

def load_results_for(filename: str) -> Tuple[List, List, List, List]:
  t1_w = []  # t1 writers
  t1_r = []  # t1 readers
  t2_w = []  # t2 writers
  t2_r = []  # t2 readers

  with open(filename, "r") as f:
    for line in f:
      line = line.strip().split(",")
      prop = float(line[1])

      if prop == 0.1:
        t1_w.append((int(line[0]), int(line[2])))
        t1_r.append((int(line[0]), int(line[3])))
      elif prop == 0.5:
        t2_w.append((int(line[0]), int(line[2])))
        t2_r.append((int(line[0]), int(line[3])))
      else:
        raise Exception()

  return (t1_w, t1_r, t2_w, t2_r)

def add_to_plot(data: Tuple, label: str, color: str, style: str):
  x = [d[0] for d in data]
  y = [d[1] for d in data]
  plt.plot(x, y, label=label, color=color, linestyle=style)

def main():
  if not os.path.exists(STD_FILENAME) or not os.path.exists(TBB_FILENAME):
    return

  (std_t1_w, std_t1_r, std_t2_w, std_t2_r) = load_results_for(STD_FILENAME)
  (tbb_t1_w, tbb_t1_r, tbb_t2_w, tbb_t2_r) = load_results_for(TBB_FILENAME)

  assert len(std_t1_w) == len(tbb_t1_w)
  assert len(std_t1_r) == len(tbb_t1_r)
  assert len(std_t2_w) == len(tbb_t2_w)
  assert len(std_t2_r) == len(tbb_t2_r)

  # NOTE: this manual plot setup leaves a lot to be desired...

  add_to_plot(std_t1_w, "std writer", color="blue", style="-")
  add_to_plot(std_t1_r, "std reader", color="blue", style="--")
  add_to_plot(tbb_t1_w, "tbb writer", color="orange", style="-")
  add_to_plot(tbb_t1_r, "tbb reader", color="orange", style="--")

  plt.xlabel("Worker Count")
  plt.ylabel("Average Lock Acquisition Latency (us)")
  plt.title("Reader/Writer Lock Acquisition Latency (Read-Heavy Workload)")
  plt.legend()

  plt.savefig(READ_HEAVY_NAME)
  plt.clf()

  add_to_plot(std_t2_w, "std writer", color="blue", style="-")
  add_to_plot(std_t2_r, "std reader", color="blue", style="--")
  add_to_plot(tbb_t2_w, "tbb writer", color="orange", style="-")
  add_to_plot(tbb_t2_r, "tbb reader", color="orange", style="--")  

  plt.xlabel("Worker Count")
  plt.ylabel("Average Lock Acquisition Latency (us)")
  plt.title("Reader/Writer Lock Acquisition Latency (Equal R/W Workload)")
  plt.legend()

  plt.savefig(EQUAL_LOAD_NAME)

if __name__ == "__main__":
  main()