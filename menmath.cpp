#include <cstdint>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

uint32_t get_answer();

struct trainer {
  uint32_t num_examples;

  trainer(uint32_t num_examples=10);
  void Sum();
  void Mul();
  void Diff();
};

trainer::trainer(uint32_t num_examples_) {
  num_examples = num_examples_;
}

void trainer::Mul()
{
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int> distrib1(0, 101);
  std::uniform_int_distribution<int> distrib2(0, 11);

  for (uint32_t i = 0; i < num_examples; i++) {
    uint32_t num_1 = distrib1(gen);
    uint32_t num_2 = distrib2(gen);

    while (1) {
      cout << num_1 << " * " << num_2 << " = ";
      uint32_t answer = get_answer();
      if( num_1 * num_2 == answer) {
        cout << "ok" << endl;
        break;
      }
      else
        cout << "Wrong." << endl;
    }
  }
}

void trainer::Diff()
{
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int> distrib(0, 101);

  uint32_t i = num_examples;
  while (i != 0) {
    uint32_t num_1 = distrib(gen);
    uint32_t num_2 = distrib(gen);
    if (num_2 > num_1)
      continue;

    while (1) {
      cout << num_1 << " - " << num_2 << " = ";
      uint32_t answer = get_answer();
      if( num_1 - num_2 == answer) {
        cout << "ok" << endl;
        break;
      }
      else
        cout << "Wrong." << endl;
    }
  i--;
  }
}

void trainer::Sum()
{
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int> distrib(0, 101);

  for (uint32_t i = 0; i < num_examples; i++) {
    uint32_t num_1 = distrib(gen);
    uint32_t num_2 = distrib(gen);

    while (1) {
      cout << num_1 << " + " << num_2 << " = ";
      uint32_t answer = get_answer();
      if( num_1 + num_2 == answer) {
        cout << "ok" << endl;
        break;
      }
      else
        cout << "Wrong." << endl;
    }
  }
}

uint32_t get_answer()
{
  uint32_t answer = 0;

  string in("");
  while (true) {
    getline(cin, in);
    if (in.empty()) {
      std::cout << "\x1B[2J\x1B[H"; // empty screen
      exit(0); //TODO: FIXME: return -1 end handle or throw an error
    }
    stringstream s(in);
    if (s >> answer)
      break;
    cout << "Invalid input.\n";
  }
  return answer;
}

int main()
{
  trainer training(5);
  training.Sum();
  training.Mul();
  training.Diff();

  return 0;
}

