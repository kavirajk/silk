#include <silk/fibers/fiber.h>
#include <silk/fibers/future.h>
#include <silk/fibers/mutex.h>
#include <silk/util/init.h>
#include <silk/util/platform.h>

#include <gtest/gtest.h>
#include <print>

namespace kavi
{

TEST(Play, run)
{
    struct Params
    {
        static int fiberMain(Params * p) noexcept
        {
            SILK_UNUSED(p);
            return 56;
        }
    };

    int ret = silk::FiberScheduler::run(Params::fiberMain, Params{});
    std::println("ret: {}", ret);
    ASSERT_EQ(ret, 56);
}

TEST(Play, fiberFuture)
{
    struct Params
    {
        static int fiberMain(Params * p) noexcept
        {
            SILK_UNUSED(p);
            return 56;
        }
    };
    silk::FiberFuture future;

    int ret = silk::FiberScheduler::run(Params::fiberMain, Params{}, &future);
    std::println("ret: {}", ret);
    ASSERT_EQ(ret, 56); // this should fail
    // Because now the scheduler run the fiber async and future holds the value sometime in the future that called can wait for.
    silk::FiberMutex mutex;
    mutex.lock();
}

}
