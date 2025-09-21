#include <bits/stdc++.h>
using namespace std;
/*
 * @brief Big num, support negative
 *
 * @code_source https://github.com/Limeoats/BigNumber
 */
class Big_num {
public:
  std::string num;
  Big_num(std::string num) : num(num) {}

  Big_num(long long num) : num(std::to_string(num)) {}

  Big_num add(const Big_num &other) {
    Big_num b1 = other > *this ? other : *this;
    Big_num b2 = other > *this ? *this : other;
    if (b1.isNegative() || b2.isNegative()) {
      if (b1.isNegative() && b2.isNegative()) {
        return b1.negate().add(b2.negate()).negate();
      } else if (b1.isNegative() && !b2.isNegative()) {
        return b1.negate().subtract(b2).negate();
      } else {
        return b2.negate().subtract(b1).negate();
      }
    }
    std::string results;
    int carry = 0;
    int diff = int(b1.num.size() - b2.num.size());
    for (int i = 0; i < diff; ++i) {
      b2.num.insert(b2.num.begin(), '0');
    }
    for (int i = int(b1.num.size() - 1); i >= 0; --i) {
      int sum = (b1.num[i] - '0') + (b2.num[i] - '0') + carry;
      carry = 0;
      if (sum <= 9 || i == 0) {
        results.insert(0, std::to_string(sum));
      } else {
        results.insert(0, std::to_string(sum % 10));
        carry = 1;
      }
    }
    return Big_num(results);
  }

  Big_num addll(long long other) { return this->add(Big_num(other)); }

  Big_num addstr(const std::string &other) { return this->add(Big_num(other)); }

  Big_num subtract(const Big_num &other) {
    Big_num b1 = *this, b2 = other;
    if (b1.isNegative() || b2.isNegative()) {
      if (b1.isNegative() && b2.isNegative()) {
        return b1.negate().subtract(b2.negate()).negate();
      } else if (b1.isNegative() && !b2.isNegative()) {
        return b1.negate().add(b2).negate();
      } else {
        return b2.negate().add(b1);
      }
    }
    std::string results;
    int n = 0, p = 0;
    bool takeOffOne = false;
    bool shouldBeTen = false;

    if (b1 < b2) {
      // Negative answer
      std::string t = b2.subtract(*this).negate().getString();
      for (unsigned int i = 1; i < t.length(); ++i) {
        if (t[i] != '0')
          break;
        t.erase(1, 1);
      }
      return Big_num(t);
    }

    // This next if-block fixes the case where the digit difference is greater
    // than 1 100 - 5 is an example. This code adds 0's to make it, for example,
    // 100 - 05, which allows the rest of the subtraction code to work.
    if (b1.num.size() - b2.getString().size() > 1) {
      for (unsigned long i = 0; i < b1.num.size() - b2.getString().size() - 1;
           ++i) {
        b2.num.insert(b2.num.begin(), '0');
      }
    }
    int i = int(b1.num.size() - 1);
    for (int j = int(b2.num.size() - 1); j >= 0; --j) {
      if (((b1.num[i] - '0') < (b2.num[j] - '0')) && i > 0) {
        n = char((b1.num[i] - '0') + 10);
        takeOffOne = true;
        if (j > 0 || b1.num[i - 1] != '0') {
          p = char((b1.num[i - 1] - '0') - 1);
          if (p == -1) {
            p = 9;
            shouldBeTen = true;
          }
          takeOffOne = false;
        }
        if (shouldBeTen) {
          int index = i - 1;
          for (int a = i - 1; (b1.num[a] - '0') == 0; --a) {
            b1.num[a] = static_cast<char>(p + '0');
            --index;
          }
          int t = (b1.num[index] - '0') - 1;
          b1.num[index] = static_cast<char>(t + '0');
        }
        b1.num[i - 1] = static_cast<char>(p + '0');
        shouldBeTen = false;
      }
      std::stringstream ss;
      if (((b1.num[i] - '0') == (b2.num[j] - '0'))) {
        ss << "0";
      } else {
        if (n <= 0) {
          ss << ((b1.num[i] - '0') - (b2.num[j] - '0'));
        } else {
          ss << (n - (b2.num[j] - '0'));
        }
      }

      results.insert(0, ss.str());
      --i;
      n = 0;
    }
    if (takeOffOne) {
      std::string number = "";
      for (int j = b1.num.length() - b2.num.length() - 1; j >= 0; --j) {
        if (b1.num[j] == '0') {
          number += "0";
          continue;
        } else {
          number.insert(number.begin(), b1.num[j]);
          int t = atoi(number.c_str());
          --t;
          b1.num.replace(0, number.size(), std::to_string(t));
          break;
        }
      }
    }
    while (i >= 0) {
      std::stringstream ss;
      if (i == 0) {
        if (b1.num[i] - '0' != 0) {
          ss << (b1.num[i] - '0');
          results.insert(0, ss.str());
        }
      } else {
        ss << (b1.num[i] - '0');
        results.insert(0, ss.str());
      }

      --i;
    }
    // In the case of all 0's, we only want to return one of them
    if (results.find_first_not_of('0') == std::string::npos) {
      results = "0";
    } else if (results[0] == '0') {
      int index = results.find_first_not_of('0');
      results = results.substr(index, results.length() - 1);
    }
    return Big_num(results);
  }

  Big_num subtractll(long long other) { return this->subtract(Big_num(other)); }

  Big_num subtractstr(const std::string &other) {
    return this->subtract(Big_num(other));
  }

  Big_num multiply(const Big_num &other) {
    Big_num b1 = other > *this ? other : *this;
    Big_num b2 = other > *this ? *this : other;
    if (b1.isNegative() || b2.isNegative()) {
      if (b1.isNegative() && b2.isNegative()) {
        return b1.negate().multiply(b2.negate());
      } else if (b1.isNegative() && !b2.isNegative()) {
        return b1.negate().multiply(b2).negate();
      } else {
        return b2.negate().multiply(b1).negate();
      }
    }
    if (b1 == 0 || b2 == 0)
      return 0;
    int carry = 0;
    int zeroCounter = 0;
    Big_num b = 0;

    for (unsigned int i = 0; i < b1.num.size() - b2.num.size(); ++i) {
      b2.num.insert(b2.num.begin(), '0');
    }
    for (long long int i = (b2.num.size() - 1); i >= 0; --i) {
      std::string rr;
      for (long long int j = int(b1.num.size() - 1); j >= 0; --j) {
        int val = ((b2.num[i] - '0') * (b1.num[j] - '0')) + carry;
        carry = 0;
        if (val > 9 && j != 0) {
          carry = val / 10;
          rr.insert(0, std::to_string(val % 10));
        } else {
          rr.insert(0, std::to_string(val));
        }
      }
      if (zeroCounter > 0) {
        for (int x = 0; x < zeroCounter; ++x) {
          rr.append("0");
        }
      }
      ++zeroCounter;
      b += Big_num(rr);
    }
    if (b.num.find_first_not_of('0') != std::string::npos) {
      b.setString(b.num.erase(0, b.num.find_first_not_of('0')));
    } else {
      // In the case of all 0's, we only want to return one of them
      b.setString("0");
    }
    return b;
  }

  Big_num multiplyll(long long other) {
    if (other == 0)
      return 0;
    if (other == 1)
      return *this;
    auto original = *this;
    for (auto i = 0; i < other - 1; ++i) {
      *this += original;
    }
    return *this;
  }

  Big_num multiplystr(const std::string &other) {
    return this->multiply(Big_num(other));
  }

  Big_num divide(const Big_num &other) {
    if (other == 0) {
      std::cerr << "You cannot divide by 0!" << std::endl;
    }
    Big_num b1 = *this, b2 = other;
    bool sign = false;
    if (b1.isNegative() && b2.isNegative()) {
      b1.negate();
      b2.negate();
    } else if (b1.isNegative() && !b2.isNegative()) {
      b1.negate();
      sign = true;
    } else if (!b1.isNegative() && b2.isNegative()) {
      b2.negate();
      sign = true;
    }
    Big_num quotient = 0;
    while (b1 >= b2) {
      b1 -= b2;
      ++quotient;
    }
    if (sign)
      quotient.negate();
    return quotient;
  }

  Big_num dividell(long long other) { return this->divide(Big_num(other)); }

  Big_num dividestr(const std::string &other) {
    return this->divide(Big_num(other));
  }

  Big_num pow(int exponent) {
    if (exponent < 0)
      std::cerr << "Powers less than 0 are not supported" << std::endl;
    if (exponent == 0)
      return Big_num("1");
    if (exponent == 1)
      return *this;
    Big_num result = 1, base = *this;
    while (exponent) {
      if (exponent & 1) {
        result *= base;
      }
      exponent >>= 1;
      base *= base;
    }
    return result;
  }

  std::string getString() const { return this->num; }

  Big_num setString(const std::string &newStr) {
    this->num = newStr;
    return *this;
  }

  Big_num negate() {
    if (this->num[0] == '-') {
      this->num.erase(0, 1);
    } else {
      this->num.insert(this->num.begin(), '-');
    }
    return *this;
  }

  Big_num trimLeadingZeros() const {
    Big_num b = *this;
    if (b.num.find_first_not_of('0') != std::string::npos) {
      b.setString(b.num.erase(0, b.num.find_first_not_of('0')));
    }
    return b;
  }

  bool equals(const Big_num &other) const { return this->num == other.num; }

  bool equals(long long other) const {
    return this->getString() == std::to_string(other);
  }

  bool equals(const std::string &other) const {
    return this->getString() == other;
  }

  unsigned int digits() {
    return this->num.length() - static_cast<int>(this->isNegative());
  }

  bool isNegative() const { return this->num[0] == '-'; }

  bool isPositive() { return !this->isNegative(); }

  bool isEven() { return this->num[this->num.length() - 1] % 2 == 0; }

  bool isOdd() { return !this->isEven(); }

  Big_num abs() {
    return Big_num(
        this->num.substr(static_cast<unsigned int>(this->isNegative())));
  }

  friend std::ostream &operator<<(std::ostream &os, const Big_num &num) {
    os << num.num;
    return os;
  }

  Big_num operator+(const Big_num &other) { return this->add(other); }

  Big_num operator+(long long b2) { return this->addll(b2); }

  Big_num operator+(const std::string &b2) { return this->addstr(b2); }

  Big_num operator-(const Big_num &b2) { return this->subtract(b2); }

  Big_num operator-(long long b2) { return this->subtractll(b2); }

  Big_num operator-(const std::string &b2) { return this->subtractstr(b2); }

  Big_num operator*(const Big_num &b2) { return this->multiply(b2); }

  Big_num operator*(long long b2) { return this->multiplyll(b2); }

  Big_num operator*(const std::string &b2) { return this->multiplystr(b2); }

  Big_num operator/(const Big_num &b2) { return this->divide(b2); }

  Big_num operator/(long long b2) { return this->dividell(b2); }

  Big_num operator/(const std::string &b2) { return this->dividestr(b2); }

  Big_num operator^(int b2) { return this->pow(b2); }

  bool operator==(const Big_num &b2) const { return this->equals(b2); }

  bool operator==(int b2) { return this->equals(b2); }

  bool operator==(const std::string &b2) { return this->equals(b2); }
  bool operator!=(const Big_num &b2) { return !this->equals(b2); }

  bool operator>(const Big_num &b2) const {
    // 負數判斷
    if (this->isNegative() || b2.isNegative()) {
      if (this->isNegative() && b2.isNegative()) {
        Big_num a = *this; // 複製一份 this，才能安全修改
        Big_num b = b2;

        a.num.erase(0, 1);
        b.num.erase(0, 1);

        // 注意：若兩者都是負數，實際上是反過來比較
        return b < a;
      }
      // 一正一負，正的一定大
      else {
        return !(this->isNegative() && !b2.isNegative());
      }
    }

    // 去掉 leading zeros
    Big_num a = this->trimLeadingZeros();
    Big_num b = b2.trimLeadingZeros();

    if (a == b) {
      return false;
    }

    // 長度不同
    if (a.num.size() > b.num.size()) {
      return true;
    } else if (b.num.size() > a.num.size()) {
      return false;
    }

    // 長度相同，比較每個位數
    for (unsigned int i = 0; i < a.num.size(); ++i) {
      unsigned int da = static_cast<unsigned int>(a.num[i] - '0');
      unsigned int db = static_cast<unsigned int>(b.num[i] - '0');

      if (da == db) {
        continue;
      }
      return da > db;
    }

    return false;
  }

  bool operator<(Big_num &b2) { return !(*this == b2) && !(*this > b2); }

  bool operator>=(Big_num &b2) { return *this > b2 || *this == b2; }

  bool operator<=(Big_num &b2) { return *this < b2 || *this == b2; }

  unsigned int operator[](int index) {
    if (this->num[index] == '-') {
      std::cerr << "You cannot get the negative sign from the number"
                << std::endl;
    }
    return static_cast<unsigned int>(this->num[index] - '0');
  }

  Big_num &operator=(long long &other) {
    this->num = std::to_string(other);
    return *this;
  }

  Big_num &operator=(std::string &other) {
    this->num = other;
    return *this;
  }

  Big_num &operator+=(const Big_num &other) {
    *this = *this + other;
    return *this;
  }

  Big_num &operator+=(long long other) {
    *this = *this + other;
    return *this;
  }

  Big_num &operator+=(const std::string &other) {
    *this = *this + other;
    return *this;
  }

  Big_num &operator-=(const Big_num &other) {
    *this = *this - other;
    return *this;
  }

  Big_num &operator-=(long long other) {
    *this = *this - other;
    return *this;
  }

  Big_num &operator-=(const std::string &other) {
    *this = *this - other;
    return *this;
  }

  Big_num &operator*=(const Big_num &other) {
    *this = *this * other;
    return *this;
  }

  Big_num &operator*=(long long other) {
    *this = *this * other;
    return *this;
  }

  Big_num &operator*=(const std::string &other) {
    *this = *this * other;
    return *this;
  }

  Big_num &operator/=(const Big_num &other) {
    *this = *this / other;
    return *this;
  }

  Big_num &operator/=(long long other) {
    *this = *this / other;
    return *this;
  }

  Big_num &operator/=(const std::string &other) {
    *this = *this / other;
    return *this;
  }

  Big_num &operator++() {
    *this += Big_num("1");
    return *this;
  }

  Big_num &operator--() {
    *this -= Big_num("1");
    return *this;
  }

  Big_num operator++(int) {
    Big_num t(this->getString());
    ++(*this);
    return t;
  }

  Big_num operator--(int) {
    Big_num t(this->getString());
    --(*this);
    return t;
  }
};
