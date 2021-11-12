
struct Vector
{
    float x;
    float y;
    Vector operator+(const float who) const;
    Vector operator-(const float who) const;
    Vector operator*(const float who) const;
    Vector operator/(const float who) const;
    bool operator==(const float who) const;
    bool operator!=(const float who) const;
    void operator=(const float who);
    Vector operator+(const Vector who) const;
    Vector operator-(const Vector who) const;
    Vector operator-() const;
    Vector operator*(const Vector who) const;
    Vector operator/(const Vector who) const;
	void operator+=(const Vector who);
	void operator+=(const float who);
    bool operator==(const Vector who) const;
    bool operator!=(const Vector who) const;
	operator bool() const;
    void operator=(const Vector who);
};