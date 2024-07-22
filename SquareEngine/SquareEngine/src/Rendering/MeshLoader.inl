namespace Square
{
    template <typename T>
    T* vectorToCArray(const std::vector<T>& vec)
    {
        T* cArray = new T[vec.size()];
        std::copy(vec.begin(), vec.end(), cArray);

        return cArray;
    }
}
