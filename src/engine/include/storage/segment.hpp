class Segment {
public:
    Segment(const std::string& filePath);

    bool appendPoint(const Point& p);
    std::optional<Point> getPoint(uint64_t id);
    bool updatePoint(const Point& p);
    bool deletePoint(uint64_t id);
    size_t size() const;

private:
    std::string _filePath;
};
