
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RECT_WIDTH = 5;
const int RECT_HEIGHT_FACTOR = 3;
const int DROPDOWN_WIDTH = 200;
const int DROPDOWN_HEIGHT = 30;
const int DROPDOWN_PADDING = 5;

// Function to swap two elements
void swap(std::vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Base class for sorting algorithms
class SortingAlgorithm {
public:
    virtual void sort(std::vector<int>& arr, sf::RenderWindow& window) = 0;
};

// Bubble sort algorithm
class BubbleSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr, sf::RenderWindow& window) override {
        int n = arr.size();
        bool isSorted = false;
        for (int i = 0; i < n - 1 && !isSorted; ++i) {
            isSorted = true;
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr, j, j + 1);
                    isSorted = false;

                    // Update window after each swap
                    window.clear();
                    for (int k = 0; k < n; ++k) {
                        sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, arr[k] * RECT_HEIGHT_FACTOR));
                        rect.setPosition(k * RECT_WIDTH, WINDOW_HEIGHT - arr[k] * RECT_HEIGHT_FACTOR);
                        window.draw(rect);
                    }
                    window.display();
                    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
    }
};

// Insertion sort algorithm
class InsertionSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr, sf::RenderWindow& window) override {
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;

                // Update window after each swap
                window.clear();
                for (int k = 0; k < n; ++k) {
                    sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, arr[k] * RECT_HEIGHT_FACTOR));
                    rect.setPosition(k * RECT_WIDTH, WINDOW_HEIGHT - arr[k] * RECT_HEIGHT_FACTOR);
                    window.draw(rect);
                }
                window.display();
                //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            arr[j + 1] = key;
        }
    }
};

// Selection sort algorithm
class SelectionSort : public SortingAlgorithm {
public:
    void sort(std::vector<int>& arr, sf::RenderWindow& window) override {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            swap(arr, i, minIndex);

            // Update window after each swap
            window.clear();
            for (int k = 0; k < n; ++k) {
                sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, arr[k] * RECT_HEIGHT_FACTOR));
                rect.setPosition(k * RECT_WIDTH, WINDOW_HEIGHT - arr[k] * RECT_HEIGHT_FACTOR);
                window.draw(rect);
            }
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
};

// Merge sort algorithm
class MergeSort : public SortingAlgorithm {
public:
    void merge(std::vector<int>& arr, int left, int mid, int right, sf::RenderWindow& window) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1);
        std::vector<int> R(n2);

        for (int i = 0; i < n1; ++i) {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; ++j) {
            R[j] = arr[mid + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                ++i;
            }
            else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }

        // Update window after each comparison
        window.clear();
        for (int p = 0; p < arr.size(); ++p) {
            sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, arr[p] * RECT_HEIGHT_FACTOR));
            rect.setPosition(p * RECT_WIDTH, WINDOW_HEIGHT - arr[p] * RECT_HEIGHT_FACTOR);
            window.draw(rect);
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }


    void mergeSort(std::vector<int>& arr, int left, int right, sf::RenderWindow& window) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid, window);
            mergeSort(arr, mid + 1, right, window);

            merge(arr, left, mid, right, window);
        }
    }

    void sort(std::vector<int>& arr, sf::RenderWindow& window) override {
        mergeSort(arr, 0, arr.size() - 1, window);
    }
};

// Quick sort algorithm
class QuickSort : public SortingAlgorithm {
public:
    int partition(std::vector<int>& arr, int low, int high, sf::RenderWindow& window) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, high);

        // Update window after each partition
        window.clear();
        for (int k = 0; k < arr.size(); ++k) {
            sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, arr[k] * RECT_HEIGHT_FACTOR));
            rect.setPosition(k * RECT_WIDTH, WINDOW_HEIGHT - arr[k] * RECT_HEIGHT_FACTOR);
            window.draw(rect);
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(75));

        return i + 1;
    }

    void quickSort(std::vector<int>& arr, int low, int high, sf::RenderWindow& window) {
        if (low < high) {
            int pi = partition(arr, low, high, window);

            quickSort(arr, low, pi - 1, window);
            quickSort(arr, pi + 1, high, window);
        }
    }

    void sort(std::vector<int>& arr, sf::RenderWindow& window) override {
        quickSort(arr, 0, arr.size() - 1, window);
    }
};

// Function to generate a random array of given size


std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    std::shuffle(arr.begin(), arr.end(), gen);
    return arr;
}

// Dropdown menu implementation
class DropdownMenu {
public:
    DropdownMenu(const std::vector<std::string>& options, sf::Font& font, const sf::Vector2f& position)
        : options_(options), font_(font), position_(position), isListShown_(false), selectedOptionIndex_(-1) {
        initialize();
    }

    void showList(bool show) {
        isListShown_ = show;
    }

    bool isListShown() const {
        return isListShown_;
    }

    void setFont(sf::Font& font) {
        font_ = font;
        initialize();
    }

    void setPosition(const sf::Vector2f& position) {
        position_ = position;
        initialize();
    }

    int getSelectedOptionIndex() const {
        return selectedOptionIndex_;
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                if (selectedOptionRect_.getGlobalBounds().contains(mousePos)) {
                    showList(!isListShown_);
                }
                else if (isListShown_ && listBackgroundRect_.getGlobalBounds().contains(mousePos)) {
                    int index = (mousePos.y - listBackgroundRect_.getPosition().y) / (listItemHeight_ + listItemSpacing_);
                    if (index >= 0 && index < options_.size()) {
                        selectedOptionIndex_ = index;
                        showList(false);
                        std::cout << "Selected: " << options_[selectedOptionIndex_] << std::endl;

                        // Handle selection here
                        handleSelection(selectedOptionIndex_, window);
                    }
                }
                else {
                    showList(false);
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(selectedOptionRect_);
        window.draw(selectedOptionText_);
        if (isListShown_) {
            window.draw(listBackgroundRect_);
            for (int i = 0; i < options_.size(); ++i) {
                window.draw(listItems_[i]);
            }
        }
    }

private:
    std::vector<std::string> options_;
    sf::Font font_;
    sf::Vector2f position_;
    bool isListShown_;
    int selectedOptionIndex_;

    sf::RectangleShape selectedOptionRect_;
    sf::Text selectedOptionText_;
    sf::RectangleShape listBackgroundRect_;
    std::vector<sf::Text> listItems_;
    float listItemHeight_;
    float listItemSpacing_;

    void initialize() {
        selectedOptionRect_.setSize(sf::Vector2f(DROPDOWN_WIDTH, DROPDOWN_HEIGHT));
        selectedOptionRect_.setFillColor(sf::Color::White);
        selectedOptionRect_.setOutlineThickness(1);
        selectedOptionRect_.setOutlineColor(sf::Color::Black);
        selectedOptionRect_.setPosition(position_);

        selectedOptionText_.setFont(font_);
        selectedOptionText_.setCharacterSize(16);
        selectedOptionText_.setFillColor(sf::Color::Black);
        selectedOptionText_.setString("Select Algorithm");
        selectedOptionText_.setPosition(position_.x + DROPDOWN_PADDING, position_.y + DROPDOWN_PADDING);

        listBackgroundRect_.setSize(sf::Vector2f(DROPDOWN_WIDTH, DROPDOWN_HEIGHT * options_.size()));
        listBackgroundRect_.setFillColor(sf::Color::White);
        listBackgroundRect_.setOutlineThickness(1);
        listBackgroundRect_.setOutlineColor(sf::Color::Black);
        listBackgroundRect_.setPosition(position_.x, position_.y + DROPDOWN_HEIGHT);

        listItemHeight_ = DROPDOWN_HEIGHT;
        listItemSpacing_ = 2;

        listItems_.resize(options_.size());
        for (int i = 0; i < options_.size(); ++i) {
            listItems_[i].setFont(font_);
            listItems_[i].setCharacterSize(16);
            listItems_[i].setFillColor(sf::Color::Black);
            listItems_[i].setString(options_[i]);
            listItems_[i].setPosition(position_.x + DROPDOWN_PADDING, position_.y + DROPDOWN_HEIGHT + (listItemHeight_ + listItemSpacing_) * i + DROPDOWN_PADDING);
        }
    }

    void handleSelection(int selectedIndex, sf::RenderWindow& window) {
        // Handle the selection here
        // You can perform different actions based on the selected index
        // For example, you can start the sorting algorithm based on the selected index

        // Generate random array
        std::vector<int> arr = generateRandomArray(WINDOW_WIDTH / RECT_WIDTH);

        // Create an instance of the selected sorting algorithm
        std::unique_ptr<SortingAlgorithm> sortingAlgorithm;
        switch (selectedIndex) {
        case 0: // Bubble Sort
            sortingAlgorithm = std::make_unique<BubbleSort>();
            break;
        case 1: // Insertion Sort
            sortingAlgorithm = std::make_unique<InsertionSort>();
            break;
        case 2: // Selection Sort
            sortingAlgorithm = std::make_unique<SelectionSort>();
            break;
        case 3: // Merge Sort
            sortingAlgorithm = std::make_unique<MergeSort>();
            break;
        case 4: // Quick Sort
            sortingAlgorithm = std::make_unique<QuickSort>();
            break;
            // Add more cases for other sorting algorithms
        }

        // Perform the sorting
        sortingAlgorithm->sort(arr, window);

        // Pause the window when the array is sorted
        bool isSorted = std::is_sorted(arr.begin(), arr.end());
        while (!isSorted) {
            isSorted = std::is_sorted(arr.begin(), arr.end());
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

int main() {
    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Algorithm Visualizer");
    window.setFramerateLimit(60);

    // Generate random array
    std::vector<int> arr = generateRandomArray(WINDOW_WIDTH / RECT_WIDTH);

    // Sorting algorithm selection
    std::vector<std::string> algorithmNames = { "Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort" };
    sf::Font font;
    if (!font.loadFromFile("Data/arial.ttf")) {
        std::cerr << "Failed to load font file" << std::endl;
        return 1;
    }
    DropdownMenu dropdown(algorithmNames, font, sf::Vector2f(10.f, 10.f));

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                dropdown.handleEvent(event, window);
            }
        }

        window.clear();

        // Draw the rectangles representing the array elements
        for (int i = 0; i < arr.size(); ++i) {
            sf::RectangleShape rect(sf::Vector2f(RECT_WIDTH, arr[i] * RECT_HEIGHT_FACTOR));
            rect.setPosition(i * RECT_WIDTH, WINDOW_HEIGHT - arr[i] * RECT_HEIGHT_FACTOR);
            window.draw(rect);
        }

        dropdown.draw(window);

        window.display();
    }

    return 0;
}