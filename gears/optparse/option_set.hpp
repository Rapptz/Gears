// The MIT License (MIT)

// Copyright (c) 2012-2014 Danny Y., Rapptz

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef GEARS_OPTPARSE_OPTION_SET_HPP
#define GEARS_OPTPARSE_OPTION_SET_HPP

#include <gears/optparse/option.hpp>
#include <set>
#include <vector>
#include <algorithm>

namespace gears {
namespace optparse {
namespace detail {
struct option_comparison {
    bool operator()(const option& lhs, const option& rhs) const {
        return lhs.name < rhs.name || (lhs.name == rhs.name && lhs.alias < rhs.alias);
    }
};
} // detail

/**
 * @ingroup optparse
 * @brief A container for holding options.
 * @details A container used for holding options. Order
 * is preserved and duplicates are removed if inserted. Note that this
 * container does not meet most of the requirements imposed by the C++
 * standard. Rather it is used exclusively for the optparse API. Compatibility
 * with the C++ standard is kept mostly to iterators which allow use of
 * the functions in `<algorithm>`.
 */
struct option_set {
private:
    std::set<option, detail::option_comparison> cache;
    std::vector<option> options;
public:
    /**
     * @brief Constructs an option_set
     * @details Constructs an option_set with a help option automatically
     * provided if wanted. The help option automatically provided is
     * `--help` with a short option `-h`. The description is
     * `"shows this message and exits"`.
     *
     * @param help Determines if help option should be automatically added.
     */
    option_set(bool help = true) {
        if(help) {
            options.emplace_back("help", 'h', "shows this message and exits");
            cache.insert(options.back());
        }
    }

    /**
     * @brief Constructs the option_set through std::initializer_list.
     * @details Constructs the option_set through std::initializer_list.
     * All duplicates are removed. Only the first duplicate is kept. A
     * duplicate is determined by having the same long name and short-name.
     * A help option is automatically provided. If the help option is
     * unwanted then a call to #remove with `"help"` as a parameter will
     * remove it.
     *
     * @param l The std::initializer_list to construct with.
     */
    option_set(std::initializer_list<option> l) {
        options.emplace_back("help", 'h', "shows this message and exits");
        cache.insert(options.back());

        for(auto&& i : l) {
            if(cache.count(i)) {
                continue;
            }

            cache.insert(i);
            options.push_back(i);
        }
    }

    /**
     * @brief Adds an option to the option_set
     * @details Adds an option to the option_set. Duplicates
     * are removed. The option is constructed as if calling
     * `option(std::forward<Args>(args)...)`, that is to say that
     * they're constructed in-place.
     *
     * @param args Arguments to pass to the #option constructor.
     */
    template<typename... Args>
    void add(Args&&... args) {
        // emplace it to the vector
        options.emplace_back(std::forward<Args>(args)...);

        // check if it's in the cache and remove it if so
        auto&& it = cache.find(options.back());
        if(it != cache.end()) {
            options.pop_back();
        }

        cache.insert(options.back());
    }

    /**
     * @brief Removes an option from the option_set
     * @details Removes an option from the option_set by
     * the argument long or short name. For example, if you want
     * to remove `--help` then `remove("help")` would remove it.
     * If the option is not found then this function has no effect.
     *
     * @param arg Long or short name to remove.
     * @return A reference to the option_set
     */
    template<typename Argument>
    option_set& remove(const Argument& arg) {
        auto&& it = std::find_if(options.begin(), options.end(), [&arg](const option& opt) {
            return opt.is(arg);
        });

        if(it != options.end()) {
            cache.erase(*it);
            options.erase(it);
        }
        return *this;
    }

    /**
     * @brief Gets a value stored by an option.
     * @details Gets a value stored by an option. The option
     * is found as if calling option::is on the `arg` parameter.
     * If the option is not found an exception is thrown. This
     * function is the equivalent of calling option::get.
     *
     * @throws std::invalid_argument Thrown if the option is not found.
     * @param arg Long or short option to retrieve value of.
     * @return The internal value stored by an option.
     */
    template<typename T, typename Argument>
    const T& get(const Argument& arg) const {
        auto&& it = std::find_if(options.begin(), options.end(), [&arg](const option& opt) {
            return opt.is(arg);
        });

        if(it == options.end()) {
            throw std::invalid_argument("option not found");
        }

        return it->template get<T>();
    }

    /**
     * @brief Gets a value stored by an option or a reasonable default.
     * @details Gets a value stored by an option or a reasonable default.
     * The option is found as if calling option::is on the `arg` parameter.
     * If the option is not found, then the default is returned.
     *
     * @param arg Long or short option to retrieve value of.
     * @return The internal value stored by an option or a reasonable default.
     */
    template<typename T, typename Argument>
    const T& get_or(const Argument& arg, const typename std::remove_reference<T>::type& def) const noexcept {
        auto&& it = std::find_if(options.begin(), options.end(), [&arg](const option& opt) {
            return opt.is(arg);
        });

        if(it == options.end()) {
            return def;
        }

        return it->template get_or<T>(def);
    }

    /**
     * @brief Checks if an option's value has been parsed.
     * @details Checks if an option's value has been parsed. The option
     * is found as if calling option::is on the `arg` parameter. This
     * function is the equivalent of calling option::is_active.
     *
     * @param arg Long or short option to retrieve value of.
     * @return `true` if the option's value has been parsed, `false` otherwise.
     */
    template<typename Argument>
    bool is_active(const Argument& arg) const noexcept {
        auto&& it = std::find_if(options.begin(), options.end(), [&arg](const option& opt) {
            return opt.is(arg);
        });

        return it != options.end() && it->is_active();
    }

    /**
     * @brief Returns the number of elements the option_set has.
     */
    size_t size() const noexcept {
        return options.size();
    }

    /**
     * @brief Checks if the option_set is empty.
     */
    bool empty() const noexcept {
        return options.empty();
    }

    //@{
    /**
     * @brief Returns an iterator pointing to the first option.
     * @details Returns an iterator pointing to the first option. This
     * member function is defined for iteration purposes and compatibility
     * with `<algorithm>`. The iterators returned are RandomAccessIterators.
     * Dereferencing this iterator is undefined behaviour if #size == 0.
     *
     * @return An iterator pointing to the first option defined.
     */
    auto begin() noexcept -> decltype(options.begin()) {
        return options.begin();
    }

    auto begin() const noexcept -> decltype(options.begin()) {
        return options.begin();
    }
    //@}

    //@{
    /**
     * @brief Returns an iterator pointing to one past the end.
     * @details Returns an iterator pointing to one past the end. This
     * member function is similar to #begin with the same rules. It's
     * undefined behaviour to dereference this iterator at all, regardless
     * of the return of #size.
     *
     * @return An iterator pointing to one past the end.
     */
    auto end() noexcept -> decltype(options.end()) {
        return options.end();
    }

    auto end() const noexcept -> decltype(options.end()) {
        return options.end();
    }
    //@}
};
} // optparse
} // gears

#endif // GEARS_OPTPARSE_OPTION_SET_HPP
