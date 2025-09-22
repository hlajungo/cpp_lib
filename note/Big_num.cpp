#include "alluneed.h"
/*
 * @brief Big num, support negative
 *
 * @code_source https://github.com/Limeoats/BigNumber
 */
class Big_num {
 public:
  string num;
  Big_num(string num) : num(num) {}
  Big_num(ll num) : num(to_string(num)) {}
  bool is_neg() const { return this->num[0] == '-'; }
  Big_num get_neg() {
    if (this->num[0] == '-') {
      this->num.erase(0, 1);
    } else {
      this->num.insert(this->num.begin(), '-');
    }
    return *this;
  }
  Big_num add(const Big_num& other) {
    Big_num b1 = other > *this ? other : *this;
    Big_num b2 = other > *this ? *this : other;
    if (b1.is_neg() || b2.is_neg()) {
      if (b1.is_neg() && b2.is_neg()) {
        return b1.get_neg().add(b2.get_neg()).get_neg();
      } else if (b1.is_neg() && !b2.is_neg()) {
        return b1.get_neg().sub(b2).get_neg();
      } else {
        return b2.get_neg().sub(b1).get_neg();
      }
    }
    string results;
    int carry = 0;
    int diff = int(b1.num.size() - b2.num.size());
    rep(i, diff) { b2.num.insert(b2.num.begin(), '0'); }
    rrep(i, b1.num.size()) {
      int sum = (b1.num[i] - '0') + (b2.num[i] - '0') + carry;
      carry = 0;
      if (sum <= 9 || i == 0) {
        results.insert(0, to_string(sum));
      } else {
        results.insert(0, to_string(sum % 10));
        carry = 1;
      }
    }
    return Big_num(results);
  }
  Big_num add(ll other) { return this->add(Big_num(other)); }
  Big_num add(const string& other) { return this->add(Big_num(other)); }
  Big_num sub(const Big_num& other) {
    Big_num b1 = *this, b2 = other;
    if (b1.is_neg() || b2.is_neg()) {
      if (b1.is_neg() && b2.is_neg()) {
        return b1.get_neg().sub(b2.get_neg()).get_neg();
      } else if (b1.is_neg() && !b2.is_neg()) {
        return b1.get_neg().add(b2).get_neg();
      } else {
        return b2.get_neg().add(b1);
      }
    }
    string results;
    int n = 0, p = 0;
    bool take1 = false;
    bool is_ten = false;
    if (b1 < b2) {
      // Negative answer
      string t = b2.sub(*this).get_neg().num;
      rep2(i, 1, (int)t.length()) {
        if (t[i] != '0') break;
        t.erase(1, 1);
      }
      return Big_num(t);
    }
    // This next if-block fixes the case where the digit difference is greater than 1
    // 100 - 5 is an example. This code adds 0's to make it, for example, 100 - 05, which
    // allows the rest of the subion code to work.
    if (b1.num.size() - b2.num.size() > 1) {
      rep(i, (int)(b1.num.size() - b2.num.size() - 1)) { b2.num.insert(b2.num.begin(), '0'); }
    }
    int i = int(b1.num.size() - 1);
    rrep(j, b2.num.size()) {
      if (((b1.num[i] - '0') < (b2.num[j] - '0')) && i > 0) {
        n = char((b1.num[i] - '0') + 10);
        take1 = true;
        if (j > 0 || b1.num[i - 1] != '0') {
          p = char((b1.num[i - 1] - '0') - 1);
          if (p == -1) {
            p = 9;
            is_ten = true;
          }
          take1 = false;
        }
        if (is_ten) {
          int index = i - 1;
          for (int a = i - 1; (b1.num[a] - '0') == 0; --a) {
            b1.num[a] = static_cast<char>(p + '0');
            --index;
          }
          int t = (b1.num[index] - '0') - 1;
          b1.num[index] = static_cast<char>(t + '0');
        }
        b1.num[i - 1] = static_cast<char>(p + '0');
        is_ten = false;
      }
      stringstream ss;
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
    if (take1) {
      string number = "";
      rrep(j, b1.num.length() - b2.num.length()) {
        if (b1.num[j] == '0') {
          number += "0";
          continue;
        } else {
          number.insert(number.begin(), b1.num[j]);
          int t = atoi(number.c_str());
          --t;
          b1.num.replace(0, number.size(), to_string(t));
          break;
        }
      }
    }
    while (i >= 0) {
      stringstream ss;
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
    if (results.find_first_not_of('0') == string::npos) {
      results = "0";
    } else if (results[0] == '0') {
      int index = results.find_first_not_of('0');
      results = results.substr(index, results.length() - 1);
    }
    return Big_num(results);
  }
  Big_num subll(ll other) { return this->sub(Big_num(other)); }
  Big_num substr(const string& other) { return this->sub(Big_num(other)); }
  Big_num multiply(const Big_num& other) {
    Big_num b1 = other > *this ? other : *this;
    Big_num b2 = other > *this ? *this : other;
    if (b1.is_neg() || b2.is_neg()) {
      if (b1.is_neg() && b2.is_neg()) {
        return b1.get_neg().multiply(b2.get_neg());
      } else if (b1.is_neg() && !b2.is_neg()) {
        return b1.get_neg().multiply(b2).get_neg();
      } else {
        return b2.get_neg().multiply(b1).get_neg();
      }
    }
    if (b1 == 0 || b2 == 0) return 0;
    int carry = 0;
    int zeroCounter = 0;
    Big_num b = 0;
    rep(i, (int)(b1.num.size() - b2.num.size())) { b2.num.insert(b2.num.begin(), '0'); }
    rrep(i, b2.num.size()) {
      string rr;
      rrep(j, b1.num.size()) {
        int val = ((b2.num[i] - '0') * (b1.num[j] - '0')) + carry;
        carry = 0;
        if (val > 9 && j != 0) {
          carry = val / 10;
          rr.insert(0, to_string(val % 10));
        } else {
          rr.insert(0, to_string(val));
        }
      }
      if (zeroCounter > 0) {
        rep(x, zeroCounter) { rr.append("0"); }
      }
      ++zeroCounter;
      b += Big_num(rr);
    }
    if (b.num.find_first_not_of('0') != string::npos) {
      b.setString(b.num.erase(0, b.num.find_first_not_of('0')));
    } else {
      // In the case of all 0's, we only want to return one of them
      b.setString("0");
    }
    return b;
  }
  Big_num multiply_ll(ll other) {
    if (other == 0) return 0;
    if (other == 1) return *this;
    auto original = *this;
    rep(i, other - 1) { *this += original; }
    return *this;
  }
  Big_num multiply_str(const string& other) { return this->multiply(Big_num(other)); }
  Big_num divide(const Big_num& other) {
    if (other == 0) { cerr << "You cannot divide by 0!" << endl; }
    Big_num b1 = *this, b2 = other;
    bool sign = false;
    if (b1.is_neg() && b2.is_neg()) {
      b1.get_neg();
      b2.get_neg();
    } else if (b1.is_neg() && !b2.is_neg()) {
      b1.get_neg();
      sign = true;
    } else if (!b1.is_neg() && b2.is_neg()) {
      b2.get_neg();
      sign = true;
    }
    Big_num quotient = 0;
    while (b1 >= b2) {
      b1 -= b2;
      ++quotient;
    }
    if (sign) quotient.get_neg();
    return quotient;
  }
  Big_num divide_ll(ll other) { return this->divide(Big_num(other)); }
  Big_num divide_str(const string& other) { return this->divide(Big_num(other)); }
  Big_num pow(int exponent) {
    if (exponent < 0) cerr << "Powers less than 0 are not supported" << endl;
    if (exponent == 0) return Big_num("1");
    if (exponent == 1) return *this;
    Big_num result = 1, base = *this;
    while (exponent) {
      if (exponent & 1) { result *= base; }
      exponent >>= 1;
      base *= base;
    }
    return result;
  }
  Big_num setString(const string& newStr) {
    this->num = newStr;
    return *this;
  }
  Big_num trimLeadingZeros() const {
    Big_num b = *this;
    if (b.num.find_first_not_of('0') != string::npos) { b.setString(b.num.erase(0, b.num.find_first_not_of('0'))); }
    return b;
  }
  bool equals(const Big_num& other) const { return this->num == other.num; }
  bool equals(ll other) const { return this->num == to_string(other); }
  bool equals(const string& other) const { return this->num == other; }
  unsigned int digits() { return this->num.length() - static_cast<int>(this->is_neg()); }
  Big_num abs() { return Big_num(this->num.substr(static_cast<unsigned int>(this->is_neg()))); }
  friend ostream& operator<<(ostream& os, const Big_num& num) {
    os << num.num;
    return os;
  }
  template<typename T>
  Big_num operator+(const T& other) {
    return this->add(other);
  }
  // Big_num
  // operator+ (ll b2)
  //{
  // return this->add (b2);
  //}
  // Big_num
  // operator+ (const string& b2)
  //{
  // return this->add (b2);
  //}
  Big_num operator-(const Big_num& b2) { return this->sub(b2); }
  Big_num operator-(ll b2) { return this->subll(b2); }
  Big_num operator-(const string& b2) { return this->substr(b2); }
  Big_num operator*(const Big_num& b2) { return this->multiply(b2); }
  Big_num operator*(ll b2) { return this->multiply_ll(b2); }
  Big_num operator*(const string& b2) { return this->multiply_str(b2); }
  Big_num operator/(const Big_num& b2) { return this->divide(b2); }
  Big_num operator/(ll b2) { return this->divide_ll(b2); }
  Big_num operator/(const string& b2) { return this->divide_str(b2); }
  Big_num operator^(int b2) { return this->pow(b2); }
  bool operator==(const Big_num& b2) const { return this->equals(b2); }
  bool operator==(int b2) { return this->equals(b2); }
  bool operator==(const string& b2) { return this->equals(b2); }
  bool operator!=(const Big_num& b2) { return !this->equals(b2); }
  bool operator>(const Big_num& b2) const {
    // 負數判斷
    if (this->is_neg() || b2.is_neg()) {
      if (this->is_neg() && b2.is_neg()) {
        Big_num a = *this;  // 複製一份 this，才能安全修改
        Big_num b = b2;
        a.num.erase(0, 1);
        b.num.erase(0, 1);
        // 注意：若兩者都是負數，實際上是反過來比較
        return b < a;
      }
      // 一正一負，正的一定大
      else {
        return !(this->is_neg() && !b2.is_neg());
      }
    }
    // 去掉 leading zeros
    Big_num a = this->trimLeadingZeros();
    Big_num b = b2.trimLeadingZeros();
    if (a == b) { return false; }
    // 長度不同
    if (a.num.size() > b.num.size()) {
      return true;
    } else if (b.num.size() > a.num.size()) {
      return false;
    }
    // 長度相同，比較每個位數
    rep(i, (int)a.num.size()) {
      unsigned int da = static_cast<unsigned int>(a.num[i] - '0');
      unsigned int db = static_cast<unsigned int>(b.num[i] - '0');
      if (da == db) { continue; }
      return da > db;
    }
    return false;
  }
  bool operator<(Big_num& b2) { return !(*this == b2) && !(*this > b2); }
  bool operator>=(Big_num& b2) { return *this > b2 || *this == b2; }
  bool operator<=(Big_num& b2) { return *this < b2 || *this == b2; }
  unsigned int operator[](int index) {
    if (this->num[index] == '-') { cerr << "You cannot get the negative sign from the number" << endl; }
    return static_cast<unsigned int>(this->num[index] - '0');
  }
  Big_num& operator=(ll& other) {
    this->num = to_string(other);
    return *this;
  }
  Big_num& operator=(string& other) {
    this->num = other;
    return *this;
  }
  Big_num& operator+=(const Big_num& other) {
    *this = *this + other;
    return *this;
  }
  Big_num& operator+=(ll other) {
    *this = *this + other;
    return *this;
  }
  Big_num& operator+=(const string& other) {
    *this = *this + other;
    return *this;
  }
  Big_num& operator-=(const Big_num& other) {
    *this = *this - other;
    return *this;
  }
  Big_num& operator-=(ll other) {
    *this = *this - other;
    return *this;
  }
  Big_num& operator-=(const string& other) {
    *this = *this - other;
    return *this;
  }
  Big_num& operator*=(const Big_num& other) {
    *this = *this * other;
    return *this;
  }
  Big_num& operator*=(ll other) {
    *this = *this * other;
    return *this;
  }
  Big_num& operator*=(const string& other) {
    *this = *this * other;
    return *this;
  }
  Big_num& operator/=(const Big_num& other) {
    *this = *this / other;
    return *this;
  }
  Big_num& operator/=(ll other) {
    *this = *this / other;
    return *this;
  }
  Big_num& operator/=(const string& other) {
    *this = *this / other;
    return *this;
  }
  Big_num& operator++() {
    *this += Big_num("1");
    return *this;
  }
  Big_num& operator--() {
    *this -= Big_num("1");
    return *this;
  }
  Big_num operator++(int) {
    Big_num t(this->num);
    ++(*this);
    return t;
  }
  Big_num operator--(int) {
    Big_num t(this->num);
    --(*this);
    return t;
  }
  // optional
  bool is_positive() { return !this->is_neg(); }
  bool is_even() { return this->num[this->num.length() - 1] % 2 == 0; }
  bool is_odd() { return !this->is_even(); }
};
