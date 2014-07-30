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

#include <catch.hpp>
#include <gears/optparse.hpp>
#include <vector>

namespace opt = gears::optparse;

TEST_CASE("optparse", "[optparse]") {
    int stuff = 0;
    opt::option_parser parser = {{
        { "version", 'v', "boolean flag" },
        { "stuff", "modifies stuff", opt::bind_to(stuff) },
        { 'f', "returns 42", opt::constant(42), opt::trait::hidden },
        { "test", 't', "requires a value", opt::value<int>() },
        { "list", 'l', "requires a list", opt::list<std::vector<int>>(3) },
        { "compose", 'c', "composes", opt::compose<std::vector<int>>() }
    }};

    SECTION("boolean switches") {
        std::vector<std::string> argv = { "dev", "--version=1" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--version" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        auto&& args = parser.raw_parse(argv.begin(), argv.end());

        REQUIRE(args.options.is_active("version"));
        REQUIRE(!args.options.is_active("stuff"));
        REQUIRE(!args.options.is_active("test"));
        REQUIRE(!args.options.is_active("compose"));
        REQUIRE(!args.options.is_active("list"));
        REQUIRE_NOTHROW(args.options.get<bool>("version"));
        REQUIRE_THROWS(args.options.get<int>("version"));
        REQUIRE(args.options.get<bool>("version"));
        REQUIRE(args.positional.empty());
        REQUIRE(args.subcommand.empty());
    }

    SECTION("bind_to") {
        std::vector<std::string> argv = { "dev", "--stuff" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--stuff=10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--stuff", "10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        auto&& args = parser.raw_parse(argv.begin(), argv.end());

        REQUIRE(!args.options.is_active("version"));
        REQUIRE(args.options.is_active("stuff"));
        REQUIRE(!args.options.is_active("test"));
        REQUIRE(!args.options.is_active("compose"));
        REQUIRE(!args.options.is_active("list"));
        REQUIRE_NOTHROW(args.options.get<int>("stuff"));
        REQUIRE_THROWS(args.options.get<bool>("stuff"));
        REQUIRE(args.options.get<int>("stuff") == 10);
        REQUIRE(stuff == 10);
        REQUIRE(args.positional.empty());
        REQUIRE(args.subcommand.empty());
    }

    SECTION("value") {
        std::vector<std::string> argv = { "dev", "--test" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "-t" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--test=10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--test", "10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "-t=10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "-t", "10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        auto&& args = parser.raw_parse(argv.begin(), argv.end());

        REQUIRE(!args.options.is_active("version"));
        REQUIRE(!args.options.is_active("stuff"));
        REQUIRE(args.options.is_active("test"));
        REQUIRE(!args.options.is_active("compose"));
        REQUIRE(!args.options.is_active("list"));
        REQUIRE_NOTHROW(args.options.get<int>("test"));
        REQUIRE_THROWS(args.options.get<bool>("test"));
        REQUIRE(args.options.get<int>("test") == 10);
        REQUIRE(args.positional.empty());
        REQUIRE(args.subcommand.empty());
    }

    SECTION("constant") {
        std::vector<std::string> argv = { "dev", "-f=10" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "-f", "10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        auto&& args = parser.raw_parse(argv.begin(), argv.end());

        REQUIRE(!args.options.is_active("version"));
        REQUIRE(!args.options.is_active("stuff"));
        REQUIRE(!args.options.is_active("test"));
        REQUIRE(!args.options.is_active("compose"));
        REQUIRE(!args.options.is_active("list"));
        REQUIRE(args.options.is_active('f'));
        REQUIRE_NOTHROW(args.options.get<int>('f'));
        REQUIRE(args.options.get<int>('f') == 42);
        REQUIRE_THROWS(args.options.get<double>('f'));
        REQUIRE(!args.positional.empty());
        REQUIRE(args.subcommand.empty());
        REQUIRE(args.positional.back() == "10");
    }

    SECTION("list") {
        std::vector<std::string> argv = { "dev", "--list" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--list", "1" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--list", "1", "2" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--list", "1", "2", "3" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--list", "1", "2", "3", "4" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        auto&& args = parser.raw_parse(argv.begin(), argv.end());

        REQUIRE(!args.options.is_active("version"));
        REQUIRE(!args.options.is_active("stuff"));
        REQUIRE(!args.options.is_active("test"));
        REQUIRE(!args.options.is_active("compose"));
        REQUIRE(args.options.is_active("list"));
        REQUIRE_THROWS(args.options.get<int>("list"));
        REQUIRE_THROWS(args.options.get<std::vector<double>>("list"));
        REQUIRE_NOTHROW(args.options.get<std::vector<int>>("list"));
        auto&& list = args.options.get<std::vector<int>>("list");
        REQUIRE(list.size() == 3);
        REQUIRE((list == std::vector<int>{ 1, 2, 3 }));
        REQUIRE(!args.positional.empty());
        REQUIRE(args.subcommand.empty());
        REQUIRE(args.positional.back() == "4");
    }

    SECTION("compose") {
        std::vector<std::string> argv = { "dev", "--compose" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "-c", "1", "--list", "1", "2", "3", "-c", "2", "--stuff", "42", "-c", "3", "10", "11", "12" };
        auto&& args = parser.raw_parse(argv.begin(), argv.end());

        REQUIRE(!args.options.is_active("version"));
        REQUIRE(args.options.is_active("stuff"));
        REQUIRE(!args.options.is_active("test"));
        REQUIRE(args.options.is_active("compose"));
        REQUIRE(args.options.is_active("list"));
        REQUIRE_THROWS(args.options.get<int>("list"));
        REQUIRE_THROWS(args.options.get<std::vector<double>>("list"));
        REQUIRE_NOTHROW(args.options.get<std::vector<int>>("list"));
        auto&& list = args.options.get<std::vector<int>>("list");
        REQUIRE(list.size() == 3);
        REQUIRE((list == std::vector<int>{ 1, 2, 3 }));
        REQUIRE(stuff == 42);
        REQUIRE_THROWS(args.options.get<int>("compose"));
        REQUIRE_THROWS(args.options.get<std::vector<double>>("compose"));
        REQUIRE_NOTHROW(args.options.get<std::vector<int>>("compose"));
        auto&& comp = args.options.get<std::vector<int>>("compose");
        REQUIRE(comp.size() == 3);
        REQUIRE((comp == std::vector<int>{ 1, 2, 3 }));
        REQUIRE(!args.positional.empty());
        REQUIRE(args.subcommand.empty());
        REQUIRE(args.positional.size() == 3);
        REQUIRE(args.positional.back() == "12");
        REQUIRE(args.positional[1] == "11");
        REQUIRE(args.positional.front() == "10");
    }

    SECTION("custom") {
        int count = 0;
        parser.add("custom", "custom stuff", opt::custom<int>([&count](const std::string&, const std::string& value) {
            count += std::stoi(value);
            return count;
        }));

        std::vector<std::string> argv = { "dev", "--custom" };
        REQUIRE_THROWS(parser.raw_parse(argv.begin(), argv.end()));
        argv = { "dev", "--custom", "2", "--custom", "10", "--custom=20", "--stuff=42", "--custom", "10" };
        auto&& args = parser.raw_parse(argv.begin(), argv.end());
        REQUIRE(!args.options.is_active("version"));
        REQUIRE(args.options.is_active("stuff"));
        REQUIRE(!args.options.is_active("test"));
        REQUIRE(!args.options.is_active("compose"));
        REQUIRE(!args.options.is_active("list"));
        REQUIRE(args.options.is_active("custom"));

        REQUIRE(stuff == 42);
        REQUIRE(args.positional.empty());
        REQUIRE(args.subcommand.empty());
        REQUIRE_NOTHROW(args.options.get<int>("custom"));
        REQUIRE_THROWS(args.options.get<int>("list"));
        REQUIRE(count == 42);
        REQUIRE(args.options.get<int>("custom") == count);
    }

    SECTION("required") {
        parser.add("req", 'r', "required", opt::value<int>(), opt::trait::required);
        std::vector<std::string> argv = { "dev" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        REQUIRE_THROWS(parser.notify());

        argv = { "dev", "--req", "10" };
        REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
        REQUIRE_NOTHROW(parser.notify());
    }
}

TEST_CASE("optparse subcommand", "[optparse-sub]") {
    int lol = 0;
    opt::option_parser parser = {{
        { "version", 'v', "boolean flag" },
        { "stuff", "tests things", opt::value<int>() }
    }};

    parser.add_subcommand({
        "test", {{
            { "testing", 't', "tests other things", opt::value<int>() },
            { "boolean", 'b', "tests" },
            { "compose", 'c', "compose", opt::compose<std::vector<int>>() },
            { "list",    'l', "lists", opt::list<std::vector<int>>(4) },
            { "bind",    'e', "binds", opt::bind_to(lol) },
            { "req",     'r', "required", opt::value<int>(), opt::trait::required }
        }}
    });

    std::vector<std::string> argv = { "dev", "--stuff", "10" };
    REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
    REQUIRE_NOTHROW(parser.notify());
    argv = { "dev", "--version" };
    REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
    REQUIRE_NOTHROW(parser.notify());
    argv = { "dev", "test", "--boolean" };
    REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
    REQUIRE_THROWS(parser.notify());
    argv = { "dev", "test", "--boolean", "--testing=10" };
    REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
    REQUIRE_THROWS(parser.notify());
    argv = { "dev", "test", "--req", "10", "--boolean", "--testing=10" };
    REQUIRE_NOTHROW(parser.raw_parse(argv.begin(), argv.end()));
    REQUIRE_NOTHROW(parser.notify());
    auto&& args = parser.raw_parse(argv.begin(), argv.end());

    REQUIRE(args.subcommand == "test");
    REQUIRE(!args.options.is_active("version"));
    REQUIRE(!args.options.is_active("stuff"));
    REQUIRE(args.options.is_active("testing"));
    REQUIRE(args.options.is_active("boolean"));
    REQUIRE(args.options.is_active("req"));
    REQUIRE(!args.options.is_active("compose"));
    REQUIRE(!args.options.is_active("list"));
    REQUIRE(!args.options.is_active("bind"));

    REQUIRE_NOTHROW(args.options.get<int>("testing"));
    REQUIRE(args.options.get<int>("testing") == 10);
    REQUIRE_THROWS(args.options.get<int>("bind"));
    REQUIRE_NOTHROW(args.options.get_or<int>("bind", 10));
    REQUIRE(args.options.get_or<int>("bind", 10) == 10);
    REQUIRE_NOTHROW(args.options.get<bool>("boolean"));
    REQUIRE_NOTHROW(args.options.get<int>("req"));
    REQUIRE(args.options.get<int>("req") == 10);
    REQUIRE(args.options.get<bool>("boolean"));
    REQUIRE(args.positional.empty());

    SECTION("complex command line") {
        argv = { "dev", "test", "-b", "-t", "10", "-c", "1", "--list", "1", "2", "3", "4", "-c=2", "-e=20", "-c", "3", "1", "2", "3" };
        auto&& arg = parser.raw_parse(argv.begin(), argv.end());

        REQUIRE(arg.subcommand == "test");
        REQUIRE(!arg.options.is_active("version"));
        REQUIRE(!arg.options.is_active("stuff"));
        REQUIRE(arg.options.is_active("testing"));
        REQUIRE(arg.options.is_active("boolean"));
        REQUIRE(arg.options.is_active("compose"));
        REQUIRE(arg.options.is_active("list"));
        REQUIRE(arg.options.is_active("bind"));

        REQUIRE_NOTHROW(arg.options.get<bool>('b'));
        REQUIRE_NOTHROW(arg.options.get<int>('t'));
        REQUIRE_NOTHROW(arg.options.get<std::vector<int>>('l'));
        REQUIRE_NOTHROW(arg.options.get<std::vector<int>>('c'));
        REQUIRE_NOTHROW(arg.options.get<int>('e'));

        REQUIRE(arg.options.get<bool>('b'));
        REQUIRE(arg.options.get<int>('t') == 10);
        REQUIRE((arg.options.get<std::vector<int>>('l') == std::vector<int>{1, 2, 3, 4}));
        REQUIRE((arg.options.get<std::vector<int>>('c') == std::vector<int>{1, 2, 3}));
        REQUIRE(arg.options.get<int>('e') == 20);
        REQUIRE(lol == 20);

        REQUIRE(!arg.positional.empty());
        REQUIRE(arg.positional.size() == 3);
        REQUIRE((arg.positional == std::vector<std::string>{"1", "2", "3"}));
    }
}
