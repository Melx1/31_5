#include <iostream>
#include <string>
#include <utility>

class Toy {
public:
    explicit Toy(std::string _name = "SomeName") : name(std::move(_name)) {};
    std::string get_name () {return name;}
private:
    std::string name;
};

class Shared_ptr_toy {
public:
    Shared_ptr_toy () {
        counter_ptr = new int(1);
        toy_ptr = new Toy();
    }

    Shared_ptr_toy (Toy* _toy) {
        counter_ptr = new int(1);
        toy_ptr = new Toy(_toy->get_name());
    }

    Shared_ptr_toy (const Shared_ptr_toy& other) {
        counter_ptr = other.counter_ptr;
        ++(*counter_ptr);
        toy_ptr = other.toy_ptr;
    }

    Shared_ptr_toy& operator= (const Shared_ptr_toy& other) {
        // Guard self assignment
        if (this == &other)
            return *this;

        --(*counter_ptr);
        if (*counter_ptr <= 0) {
            delete counter_ptr;
            delete toy_ptr;
        }

        counter_ptr = other.counter_ptr;
        ++(*counter_ptr);
        toy_ptr = other.toy_ptr;

        return *this;
    }

    Toy& operator* () const {
      return *toy_ptr;
    }

    Toy* operator-> () const {
        return toy_ptr;
    }

    const int& use_count () {
        return *counter_ptr;
    }

    Toy* get () {
        return toy_ptr;
    }

    ~Shared_ptr_toy () {
        --(*counter_ptr);
        if (*counter_ptr <= 0) {
            delete counter_ptr;
            delete toy_ptr;
        }
    }

private:
    int* counter_ptr = nullptr;
    Toy* toy_ptr = nullptr;
};

Shared_ptr_toy make_shared_toy (Toy& t) {
    return {&t};
}

Shared_ptr_toy make_shared_toy (std::string _name) {
    Toy toy(std::move(_name));
    return {&toy};
}

int main() {
    Toy some_toy("bone");
    Shared_ptr_toy ptr11 = make_shared_toy("ball");
    Shared_ptr_toy ptr12 = make_shared_toy(some_toy);

    {
        Shared_ptr_toy sptr1 (new Toy ("abra"));
        Shared_ptr_toy sptr2 = sptr1;
        Shared_ptr_toy sptr3 = sptr2;

        std::cout << "sptr1 toy name  = " << sptr1->get_name() << ", use_count() = "
                  << sptr1.use_count() << '\n';

        // Reset the shared_ptr sptr1, hand it a fresh instance of Foo.
        // The old instance will stay shared between sptr2 and sptr3.
        std::cout << "call sptr1.reset()...\n";
        sptr1 = Shared_ptr_toy (new Toy ());

        std::cout << "After reset():\n"
                  << "sptr1.use_count() = " << sptr1.use_count()
                  << ", sptr1 @ " << sptr1.get() << '\n'
                  << "sptr2.use_count() = " << sptr2.use_count()
                  << ", sptr2 @ " << sptr2.get() << '\n'
                  << "sptr3.use_count() = " << sptr3.use_count()
                  << ", sptr3 @ " << sptr3.get() << '\n'
                  << "Leaving the scope...\n";
    }   // Calls two destructors of: 1) Foo owned by sptr1,
    // 2) Foo shared between sptr2/sptr3.

    return 0;
}
