/**
 * @file base_thread.cpp
 * @brief 
 * @details
 * @author AstraCod3
 * @date June 28, 2026
 * @version 1.0.0
 * 
 * @note
 * @warning
 * @see 
 * @todo
 * @deprecated
 * @def
 */

#include <future>
#include <chrono>
#include <atomic>

#include <gtest/gtest.h>

#include "../thread_base/cthread_base.hpp"

/**
 * @namespace ns_unit_test
 * @brief Contains all the unit tests for the multi-threading wrappers and thread components.
 * @details This namespace isolates test components, mocks, and test fixtures from the production code.
 */
namespace ns_unit_test_base_thread {
    /**
     * @brief Mock worker class used to inject test logic into the thread execution.
     * @details Inherits from the base thread wrapper to override and test the core virtual function.
     */
    class TestThreadWorker : public ns_thread_base::cthread_base {
        public:
        std::function<void()> logicaDiTest = nullptr; ///< Custom test logic injection point.

        protected:
        /**
         * @brief Overridden thread loop that executes the injected test logic.
         */
        void thread_function() override {
            if (logicaDiTest) {
                logicaDiTest();
            }
        }
    };

    /**
     * @brief Verify that the virtual function executes successfully within 2 seconds.
     * @details This test ensures that the thread starts properly, executes the overridden 
     *          virtual method, and that the destroy sequence does not encounter a deadlock.
     */
    TEST(ThreadAbstractTest, SingleExecution) {

        TestThreadWorker worker;

        std::promise<void> threadHaEseguitoLaVirtual;

        std::future<void> futuro = threadHaEseguitoLaVirtual.get_future();

        // Inject the lambda function to signal the test when the thread runs
        worker.logicaDiTest = [&threadHaEseguitoLaVirtual]() {
            threadHaEseguitoLaVirtual.set_value(); // Segnala il successo
        };

        // --- ACT ---
        // Initialize and spin up the worker thread
        worker.create();

        // Unlock the conditional wait to let the thread execute
        worker.run();

        // --- ASSERT ---
        // Verify that the virtual function executes within 2 seconds
        auto statusLavoro = futuro.wait_for(std::chrono::seconds(2));
        EXPECT_EQ(statusLavoro, std::future_status::ready) << "La funzione virtuale non è stata eseguita.";

        // Safeguard: Execute destroy asynchronously to prevent the unit test from hanging in case of a deadlock
        std::future<void> futuroDestroy = std::async(std::launch::async, [&worker]() {
            worker.destroy();
        });

        // Verify that the destroy/join sequence finishes within 2 seconds
        auto statusDestroy = futuroDestroy.wait_for( std::chrono::seconds(2) );
        EXPECT_EQ(statusDestroy, std::future_status::ready) << "destroy() è rimasta bloccata in deadlock.";
    }

    /**
     * @brief Verify that the thread worker can be triggered for multiple consecutive executions.
     * @details This test ensures that the condition variable or signaling mechanism inside 
     *          the thread allows the worker to be safely unblocked and run multiple times (`run()`)
     *          without getting stuck or losing events.
     */
    TEST(ThreadAbstractTest, MultipleExecution) {
        TestThreadWorker worker;
        std::atomic<int> counter{0};

        worker.logicaDiTest = [&counter]() {
            counter++;
        };

        worker.create();

        // First block
        worker.run();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        EXPECT_EQ(counter.load(), 1);

        // Second block
        worker.run();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        EXPECT_EQ(counter.load(), 2);

        // Clean
        worker.destroy();
    }

} // ns_unit_test_base_thread

/*
 * @brief Main function
 */
void main(int _argc, char* _argv[]) {
    /*
     * @brief Initi Google Test framework with arguments passando i parametri della riga di comando
     */
    ::testing::InitGoogleTest(&_argc, _argv);
    
    /*
     * @brief Execute all TEST e TEST_F macro return 0 succeded,  otherwise return 1
     */ 
    int ret = RUN_ALL_TESTS();
    if ( ret != 0 ) {
        throw std::runtime_error("!ERROR! Unit test failure\n");
    }

}
