#include "fmt/format.h"

#define FAILURE(msg, ...)                                                      \
  {                                                                            \
    fmt::print(stderr, "{}:{}: \033[31mFAILURE\033[0m: " #msg "\n", __FILE__,  \
               __LINE__, __VA_ARGS__);                                         \
    testing.failed = true;                                                     \
  }

#define EXPECT_EQ(a, b)                                                        \
  {                                                                            \
    if ((a) != (b)) {                                                          \
      FAILURE("{} != {}\nWhich is {} != {}", #a, #b, (a), (b));                \
    }                                                                          \
  }

#define EXPECT_NE(a, b)                                                        \
  {                                                                            \
    if ((a) == (b)) {                                                          \
      FAILURE("{} == {}\nWhich is {} == {}", #a, #b, (a), (b));                \
    }                                                                          \
  }

#define EXPECT_TRUE(a)                                                         \
  {                                                                            \
    if (!(a)) {                                                                \
      FAILURE("{} is not true", #a);                                           \
    }                                                                          \
  }

#define EXPECT_FALSE(a)                                                        \
  {                                                                            \
    if ((a)) {                                                                 \
      FAILURE("{} is not false", #a);                                          \
    }                                                                          \
  }

struct Testing {
  bool failed;
  std::string title;

  Testing(std::string const& t) : failed{false}, title{t} {
    fmt::print(stderr, "\033[1mTesting\033[0m: {}\n", title);
  }
  ~Testing() {
    if (!failed) {
      fmt::print(stderr, "\033[32mSUCCESS\033[0m: {}\n", title);
    } else {
      fmt::print(stderr, "\033[31mFAILURE\033[0m: {}\n", title);
    }
  }
};

#define TEST(Case) void TEST_##Case(Testing testing = {#Case})
