class Date{
    private :
    int m_year;
    int m_month;
    int m_day;

    public :
    int getDay() const { 
        return m_day;
    }
    int getMonth() const {
        return m_month;
    }
    int getYear() const {
        return m_year;
    }

    void setDay(int val) {
        m_day=val;
    }
    void setMonth(int val) {
        m_month=val;
    }
    void setYear(int val) {
        m_year=val;
    }

    Date(int day , int month , int year);
    void printDate() const;
};