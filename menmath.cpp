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

int main(int argc, char* argv[])
{
    using namespace clipp;
string infile;
bool tr = false, rot = false;
double x = 0, y = 0, z = 0;
double phi = 0, theta = 0;

auto cli = (
    option("-translate").set(tr) & value("x", x) & value("y", y) & value("z", z)
);
    if(parse(argc, argv, cli)) {
        if(!tr && !rot) {
            cout << "nothing will be done with file '" << infile << "'\n";
        }
        else {
            cout << "transforming content of file '" << infile << "'\n";
            if(tr) {
                cout << "translating objects by vector ("
                     << x << ", " << y << ", " << z << ")\n";
            }
            if(rot) {
                cout << "rotating objects about azimuth = " << phi
                     << " and polar angle = " << theta << '\n';
            }
        }
    }
    else {
        cout << "Usage:\n" << usage_lines(cli, argv[0]) << '\n';
    }
exit(0);

  summ sum0(10, 5, 8, 5, 8);
  sum0.execise();

  summ sum1;
  sum1.execise();

  mult mul0;
  mul0.execise();

  diff dif;
  dif.execise();
  change(10, 2000).execise();

  return 0;
}

