#include "alluneed.h"
/*
 * Supported
 * neg + - * / == > < >=
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
  Big_num set_str(const string& newStr) {
    this->num = newStr;
    return *this;
  }
  Big_num trim_lead_0() const {
    Big_num b = *this;
    if (b.num.find_first_not_of('0') != string::npos) { b.set_str(b.num.erase(0, b.num.find_first_not_of('0'))); }
    return b;
  }
  bool equals(const Big_num& other) const { return this->num == other.num; }
  bool operator==(const Big_num& b2) const { return this->equals(b2); }
  bool operator>(const Big_num& b2) const {
    if (this->is_neg() || b2.is_neg()) {
      if (this->is_neg() && b2.is_neg()) {
        Big_num a = *this;
        Big_num b = b2;
        a.num.erase(0, 1);
        b.num.erase(0, 1);
        return b < a;
      }
      else {
        return !(this->is_neg() && !b2.is_neg());
      }
    }
    Big_num a = this->trim_lead_0();
    Big_num b = b2.trim_lead_0();
    if (a == b) { return false; }
    if (a.num.size() > b.num.size()) {
      return true;
    } else if (b.num.size() > a.num.size()) {
      return false;
    }
    rep(i, (int)a.num.size()) {
      unsigned int da = static_cast<unsigned int>(a.num[i] - '0');
      unsigned int db = static_cast<unsigned int>(b.num[i] - '0');
      if (da == db) { continue; }
      return da > db;
    }
    return false;
  }
  bool operator<(Big_num& b2) { return !(*this == b2) && !(*this > b2); }
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
  bool operator>=(Big_num& b2) { return *this > b2 || *this == b2; }
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
    if (results.find_first_not_of('0') == string::npos) {
      results = "0";
    } else if (results[0] == '0') {
      int index = results.find_first_not_of('0');
      results = results.substr(index, results.length() - 1);
    }
    return Big_num(results);
  }
  Big_num mul(const Big_num& other) {
    Big_num b1 = other > *this ? other : *this;
    Big_num b2 = other > *this ? *this : other;
    if (b1.is_neg() || b2.is_neg()) {
      if (b1.is_neg() && b2.is_neg()) {
        return b1.get_neg().mul(b2.get_neg());
      } else if (b1.is_neg() && !b2.is_neg()) {
        return b1.get_neg().mul(b2).get_neg();
      } else {
        return b2.get_neg().mul(b1).get_neg();
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
      b = b.add(Big_num(rr));
    }
    if (b.num.find_first_not_of('0') != string::npos) {
      b.set_str(b.num.erase(0, b.num.find_first_not_of('0')));
    } else {
      b.set_str("0");
    }
    return b;
  }
  Big_num div(const Big_num& other) {
    if (other == 0) { cerr << "You cannot div by 0!" << endl; }
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
      b1 = b1.sub(b2);
      quotient.add(Big_num("1"));
    }
    if (sign) quotient.get_neg();
    return quotient;
  }
};
