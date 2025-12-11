#include <cstdint>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <random>

#include "include/clipp.h"

using namespace std;

uint32_t get_answer();

class summ {
  uint32_t num_examples;
  uint32_t l1;
  uint32_t h1;
  uint32_t l2;
  uint32_t h2;

  public:
  summ(uint32_t num_examples_=10, uint32_t l1_=11, uint32_t h1_=101,
      uint32_t l2_=11, uint32_t h2_=101);
  void execise();
};

class mult {
  uint32_t num_examples;
  uint32_t l1;
  uint32_t h1;
  uint32_t l2;
  uint32_t h2;

  public:
  mult(uint32_t num_examples_=10, uint32_t l1_=11, uint32_t h1_=101,
      uint32_t l2_=0, uint32_t h2_=11);
  void execise();
};

class diff {
  uint32_t num_examples;
  uint32_t l;
  uint32_t h;

  public:
  diff(uint32_t num_examples_=10, uint32_t l_=0, uint32_t h_=101);
  void execise();
};

class change {
  uint32_t num_examples;
  uint32_t bancnote;

  public:
  change(uint32_t num_examples_, uint32_t bancnote_);
  void execise();
};

change::change(uint32_t num_examples_=10, uint32_t bancnote_=100)
{
  num_examples = num_examples_;
  bancnote = bancnote_;
}

summ::summ(uint32_t num_examples_, uint32_t l1_, uint32_t h1_,
           uint32_t l2_, uint32_t h2_)
{
  num_examples = num_examples_;
  l1 = l1_;
  h1 = h1_;
  l2 = l2_;
  h2 = h2_;
}

void summ::execise()
{
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int> distrib_1(l1, h1);
  std::uniform_int_distribution<int> distrib_2(l2, h2);

  for (uint32_t i = 0; i < num_examples; i++) {
    uint32_t num_1 = distrib_1(gen);
    uint32_t num_2 = distrib_1(gen);

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

mult::mult(uint32_t num_examples_, uint32_t l1_, uint32_t h1_,
           uint32_t l2_, uint32_t h2_)
{
  num_examples = num_examples_;
  l1 = l1_;
  h1 = h1_;
  l2 = l2_;
  h2 = h2_;
}

void mult::execise()
{
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int> distrib1(l1, h1);
  std::uniform_int_distribution<int> distrib2(l2, h2);

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

diff::diff(uint32_t num_examples_, uint32_t l_, uint32_t h_)
{
  num_examples = num_examples_;
  l = l_;
  h = h_;
}

void change::execise()
{
  random_device rd;  // a seed source for the random number engine
  mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  uniform_int_distribution<int> distrib(1, bancnote);

  uint32_t i = num_examples;
  while (i != 0) {
    uint32_t num = distrib(gen);
    if (num > bancnote)
      continue;

    while (1) {
      cout << bancnote << " - " << num << " = ";
      uint32_t answer = get_answer();
      if(bancnote - num == answer) {
        cout << "ok" << endl;
        break;
      }
      else
        cout << "Wrong." << endl;
    }
  i--;
  }
}

void diff::execise()
{
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int> distrib(l, h);

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
// ./menmath --warm 5 5 8 5 8 --sum 10 11 101 11 101 --mult 10 11 101 0 11 --diff 10 0 101 --change 10 2000
int main(int argc, char* argv[])
{
  using namespace clipp;

  bool fwarm = false;
  bool fsum = false;
  bool fmult = false;
  bool fdiff = false;
  bool fchange = false;
  uint32_t n[5] = {0}; //TODO: FIXME: define macro or const
  uint32_t l1[5] = {0}; //TODO: FIXME: define macro or const
  uint32_t h1[5] = {0}; //TODO: FIXME: define macro or const
  uint32_t l2[5] = {0}; //TODO: FIXME: define macro or const
  uint32_t h2[5] = {0}; //TODO: FIXME: define macro or const
  uint32_t note = 0;

  auto cli = (
      option("--warm").set(fwarm) & value("n", n[0]) & value("l1", l1[0]) & value("h1", h1[0]) & value("l2", l2[0]) & value("h2", h2[0]),
      option("--sum").set(fsum) & value("n", n[1]) & value("l1", l1[1]) & value("h1", h1[1]) & value("l2", l2[1]) & value("h2", h2[1]),
      option("--mult").set(fmult) & value("n", n[2]) & value("l1", l1[2]) & value("h1", h1[2]) & value("l2", l2[2]) & value("h2", h2[2]),
      option("--diff").set(fdiff) & value("n", n[3]) & value("l1", l1[3]) & value("h1", h1[3]),
      option("--change").set(fchange) & value("n", n[4]) & value("note", note)
    );

    if(parse(argc, argv, cli)) {
      if(fwarm)
        summ(n[0], l1[0], h1[0], l2[0], h2[0]).execise();
      if(fsum)
        summ(n[1], l1[1], h1[1], l2[1], h2[1]).execise();
      if(fmult)
        mult(n[2], l1[2], h1[2], l2[2], h2[2]).execise();
      if(fdiff)
        diff(n[3], l1[3], h1[3]).execise();
      if(fchange)
        change(n[4], note).execise();

      summ(5, 5, 8, 5, 8).execise();
      summ().execise();
      mult().execise();
      diff().execise();
      change(10, 2000).execise();
    }
    else
      cout << "Usage:\n" << usage_lines(cli, argv[0]) << '\n';

  return 0;
}

