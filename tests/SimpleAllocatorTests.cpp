#include "catch_amalgamated.hpp"

#include "SimpleStaticAllocator.h"

#define CATCH_CONFIG_MAIN

using TestAllocatorType = uint8_t;
static constexpr size_t TEST_POOL_SIZE = 10;

static void dummyLock() {}

static void dummyRelease() {}

TEST_CASE("Can create allocator", "[SimpleStaticAllocator]") {
    AllocatorLib::SimpleStaticAllocator<TestAllocatorType, 3, TEST_POOL_SIZE> allocator(dummyLock, dummyRelease);

    REQUIRE(allocator.size() == 3);
}

TEST_CASE("Can allocate chunk", "[SimpleStaticAllocator]") {
    AllocatorLib::SimpleStaticAllocator<TestAllocatorType, 1, TEST_POOL_SIZE> allocator(dummyLock, dummyRelease);

    auto chunk = allocator.allocate();

    REQUIRE(chunk != nullptr);
    REQUIRE(allocator.count() == TEST_POOL_SIZE - 1);
}

TEST_CASE("Can free chunk", "[SimpleStaticAllocator]") {
    AllocatorLib::SimpleStaticAllocator<TestAllocatorType, 1, TEST_POOL_SIZE> allocator(dummyLock, dummyRelease);

    auto chunk = allocator.allocate();
    allocator.free(chunk);

    REQUIRE(chunk == nullptr);
    REQUIRE(allocator.count() == TEST_POOL_SIZE);
}

TEST_CASE("Can't free already freed chunk", "[SimpleStaticAllocator]") {
    AllocatorLib::SimpleStaticAllocator<TestAllocatorType, 1, TEST_POOL_SIZE> allocator(dummyLock, dummyRelease);

    auto chunk0 = allocator.allocate();
    auto chunk1 = allocator.allocate();
    allocator.free(chunk0);
    allocator.free(chunk0);

    REQUIRE(allocator.count() == TEST_POOL_SIZE - 1);
}

TEST_CASE("Can't allocate more than pool capacity", "[SimpleStaticAllocator]") {
    AllocatorLib::SimpleStaticAllocator<TestAllocatorType, 5, TEST_POOL_SIZE> allocator(dummyLock, dummyRelease);

    auto chunk0 = allocator.allocate();
    auto chunk1 = allocator.allocate();
    auto chunk2 = allocator.allocate();

    REQUIRE(chunk0 != nullptr);
    REQUIRE(chunk1 != nullptr);
    REQUIRE(chunk2 == nullptr);
    REQUIRE(allocator.count() == 0);
}