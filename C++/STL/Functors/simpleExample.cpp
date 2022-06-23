class Linear
{
private:
    double slope;
    double y0;

public:
    //Constructor
    Linear(double sl_ = 1, double y_ = 0) : slope(sl_), y0(y_) { }
    //Overloaded operator () to use an object as a function
    double operator()(double x) { return y0 + slope * x; }
};

int main(int argc, char const *argv[])
{
    Linear lin1{2, 3};
    Linear lin2{3, 4};

    double value1 = lin1(5);
    double value2 = lin2(5);

    return 0;
}
