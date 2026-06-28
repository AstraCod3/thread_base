/**
 * @file quick_sort.cpp
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

#include <iostream>
#include <sstream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <algorithm> // std::sort
#include <utility> // std::swap
#include <limits> // std::numeric_limits

#include "../thread_base/cthread_base.hpp"

namespace ns_quick_sort {

    /**
     * @class cquick_sort
     * @brief Example illustrating how to use ns_base_thread::cthread_base
     */
    class cquick_sort : public ns_thread_base::cthread_base {

    public:

        /**
         * @brief Costructor.
         */
        cquick_sort() :
            delta_time_ms( std::chrono::microseconds::zero() )
        { }

        /**
         * @brief Costructor.
         */
        cquick_sort( std::string& _name_of_thread ) :
            ns_thread_base::cthread_base( _name_of_thread ), 
            delta_time_ms( std::chrono::microseconds::zero() )
        { }

        /**
         * @brief Destructor.
         */
        virtual ~cquick_sort()
        { }

        /**
         * @brief Vector containing elements to be sort.
         */
        std::vector<int> buffer;

        /**
         * @brief Delta time taken to execute thread microseconds.
         */
        std::chrono::microseconds delta_time_ms;

        /**
         * @brief Partitions the vector using the last element as the pivot.
         * 
         * 1. Select the last element as the pivot.
         * 2. Move elements smaller than or equal to the pivot to the left side.
         * 3. Place the pivot immediately after the last smaller element found.
         * 
         * @param arr The vector to be partitioned.
         * @param low The starting index of the partition.
         * @param high The ending index of the partition (contains the pivot).
         * @return size_t The final index of the pivot.
         */
        size_t partition(std::vector<int>& arr, size_t low, size_t high) {
            int pivot = arr[high];
            size_t i = low; // 'i' tracks the boundary of elements smaller than the pivot

            for (size_t j = low; j < high; ++j) {
                if (arr[j] <= pivot) {
                    std::swap(arr[i], arr[j]);
                    ++i; // Advance the boundary only AFTER the swap
                }
            }
            
            // Move the pivot to its correct sorted position
            std::swap(arr[i], arr[high]);
            return i;
        }

        /**
         * @brief Recursively sorts a vector using the quicksort algorithm.
         * @param arr The vector to be sorted.
         * @param low The starting index of the current partition.
         * @param high The ending index (inclusive) of the current partition.
         */
        void quick_sort(std::vector<int>& arr, size_t low, size_t high) {
            if (low < high) {
                // pIdx is the index where the pivot is in its correct position.
                size_t pIdx = partition(arr, low, high);

                // Safely sort the left side, avoiding underflow if pIdx is 0
                if (pIdx > 0) {
                    quick_sort(arr, low, pIdx - 1);
                }
                
                // Sort the right side
                quick_sort(arr, pIdx + 1, high);
            }
        }

        protected:

        /**
         * @brief Example of the implementation of "thread_function()" inherited from ns_base_thread::cthread_base
         */
        void thread_function() override {
            auto start_clock = std::chrono::high_resolution_clock::now();
            quick_sort( buffer, 0, buffer.size()-1 );
            auto stop_clock = std::chrono::high_resolution_clock::now();
            delta_time_ms = std::chrono::duration_cast<std::chrono::microseconds>(stop_clock  - start_clock );
        }

    }; // cquick_sort


    /**
     * @class c_manager_quick_sort 
     * @brief Handler class
     */
    class c_manager_quick_sort {

        public :

            /**
             * @brief Costructor.
             */
            c_manager_quick_sort () :
                vector_size(0),
                min_value(0),
                max_value(0),
                num_of_threads(0)
            { }

            /**
             * @brief Destructor.
             */
            virtual ~c_manager_quick_sort ()
            { }

            /**
             * @brief
             * @throw
             */
            void check_and_set_parameters(  const size_t& _vector_size,
                                    const int& _min_value,
                                    const int& _max_value,
                                    const int& _num_of_threads) { 

                // Check size of vector to sort
                const size_t vrandom_max_size = vrandom.max_size();
                if ( _vector_size > vrandom_max_size  ) {
                    std::string str_vector_size = std::to_string( _vector_size );
                    std::string str_vrandom_max_size = std::to_string( vrandom_max_size );
                    std::string msg_ex = std::string("vector size " + str_vector_size + " > " + str_vrandom_max_size);
                    throw std::runtime_error(msg_ex.c_str());
                }

                long int min_value_check = (std::numeric_limits<int>::min)();
                long int max_value_check = (std::numeric_limits<int>::max)();

                // Check min and max value range
                // min_value_check < _min_value < max_value_check
                if ( _min_value < min_value_check ) {
                    std::string str_min_value = std::to_string( _min_value );
                    std::string str_min_value_check = std::to_string( min_value_check );
                    std::string msg_ex = std::string("Min value " + str_min_value + " < " + str_min_value_check);
                    throw std::runtime_error(msg_ex.c_str());
                }
                if ( _min_value > max_value_check ) {
                    std::string str_min_value = std::to_string( _min_value );
                    std::string str_max_value_check = std::to_string( max_value_check );
                    std::string msg_ex = "Min value " + str_min_value + " > " + str_max_value_check;
                    throw std::runtime_error(msg_ex.c_str());
                }

                // min_value_check < _max_value < max_value_check
                if ( _max_value < min_value_check ) {
                    std::string str_max_value  = std::to_string( _max_value );
                    std::string str_min_value_check = std::to_string( min_value_check );
                    std::string msg_ex = "Max value " + str_max_value + " < " + str_min_value_check;
                    throw std::runtime_error(msg_ex.c_str());
                }
                if ( _min_value > max_value_check ) {
                    std::string str_max_value  = std::to_string( _min_value );
                    std::string str_max_value_check = std::to_string( max_value_check );
                    std::string msg_ex = "Max value " + str_max_value + " > " + str_max_value_check;
                    throw std::runtime_error(msg_ex.c_str());
                }

                /**
                 * @todo check num. of threads.
                 */

                vector_size = _vector_size;
                min_value = _min_value;
                max_value = _max_value;
                num_of_threads = _num_of_threads;

                std::cout <<  " num of threads : " << num_of_threads << std::endl;
                std::cout <<  " size : " << vector_size << std::endl;
                std::cout <<  " min_value : " << min_value << std::endl;
                std::cout <<  " max_value : " << max_value << std::endl;
            }

            /**
             * @brief
             */
            void sort_vector(const size_t& _vector_size,
                            const int& _min_value,
                            const int& _max_value,
                            const int& _num_of_threads) { 

                check_and_set_parameters(_vector_size, _min_value, _max_value, _num_of_threads);
                
                init_vectors();

                init_threads();

                create_threads();

                auto start_clock_total = std::chrono::high_resolution_clock::now();
                
                run_threads();
                check_all_threads_executed();
                
                auto stop_clock_total = std::chrono::high_resolution_clock::now();
                auto delta_time_ms_total = std::chrono::duration_cast<std::chrono::microseconds>(stop_clock_total  - start_clock_total );
                std::cout << " Delta time main [millisec] " << static_cast<double>(delta_time_ms_total.count()) / 1000.0 << "\n";     

                destroy_threads();
                
                statistics();

                merge_and_sort( );

                clear_vectors();
            }

        private :

            /**
             * @brief The total number of elements allocated for both input and output vectors.
             * @details This size is applied to `vrandom` and `vsorted` during initialization.
             */
            size_t vector_size = 1ULL << 16;

            /**
             * @brief Min value.
             */
            int min_value = 10;

            /**
             * @brief Max value.
             */
            int max_value = 10000000;

            /**
             * @brief Number of threads.
             */
            int num_of_threads = 1ULL << 4; 

            /**
             * @brief Vector of threads
             */
            std::vector< std::shared_ptr<cquick_sort> > vquick_sort;

            /**
             * @brief The vector filled with random number.
             */
            std::vector<int> vrandom;

            /**
             * @brief The vector sorted
             */
            std::vector<int> vsorted;

            /**
             * @brief This function initialize the vectors.
             */
            void init_vectors(){
                // std::cout <<  " Init vectors\n";
                vrandom.reserve( vector_size );
                int range = max_value - min_value + 1;
                for (size_t i = 0; i < vector_size; ++i)
                    vrandom.push_back( min_value + (std::rand() % range) );
                vsorted.reserve( vrandom.size() );
            }

            /*
             * @brief Clear the vectors
             */
            void clear_vectors() {
                vrandom.clear();
                vsorted.clear();
                vquick_sort.clear();
            }

            /**
             * @brief Merge, Sort and Check
             *      1. Merge the vectors for each threads
             *      2. Sort the vector sorted.
             *      3. Check if the vector is sorted.
             **/
            void merge_and_sort() {
                std::cout << " Merge and Sort\n";
                // 1. Merge the vectors for each threads
                for (auto& t : vquick_sort)
                    vsorted.insert( vsorted.end(), t->buffer.begin(), t->buffer.end() );
                
                // 2. Sort the vector sorted.
                std::sort( vsorted.begin(), vsorted.end() );

                // 3. Check if the vector is sorted.
                if ( std::is_sorted(vsorted.begin(), vsorted.end()) )
                    std::cout << " Vector is sorted\n";
                else 
                    std::cout << " Vector is not sorted\n";
            }

            /**
             * @brief This function is BLOCKING.
             *        1. Calculate the number of elements to assign to each thread
             *           and calculate the remaining remainder to add to the last thread.
             *        2. Allocate an instance of cquick_sort.
             *        3. Calculate the min and max range to set up an instance of cquick_sort.
             *        4. Populate the vquick_sort vector.
             */
            void init_threads() {
                std::cout << " Initializing threads\n";
                // 1. Calculate the number of elements to assign to each thread
                size_t elem_num_for_threads = static_cast<size_t>( vector_size / num_of_threads );
                size_t remain_partition = static_cast<size_t>( vector_size % num_of_threads ); // Rinominata variabile
                // std::cout << "  elem_num_for_threads : " << elem_num_for_threads << std::endl;
                // std::cout << "  remain_partition : " << remain_partition << std::endl;

                for ( int t = 0; t < num_of_threads; t++ ) {
                    std::string name_of_thread = "THR_" + std::to_string(t);
                    // 2. Allocate an instance of cquick_sort
                    std::shared_ptr<cquick_sort> ptr_thr = std::make_shared< cquick_sort >( name_of_thread ) ;
                    // 3. Calculate min and max range to set an instance of cquick_sort
                    size_t range_min = elem_num_for_threads  * t;
                    size_t range_max = range_min + elem_num_for_threads - 1  ;
                    if ( t == ( num_of_threads - 1) )
                        range_max += remain_partition;
                    ptr_thr->buffer.insert( ptr_thr->buffer.end(),
                                            vrandom.begin()+range_min,
                                            vrandom.begin()+range_max );
                    // 4. Populate vquick_sort vector.
                    vquick_sort.push_back( ptr_thr );
                    // std::cout << "  " << ptr_thr->get_name() << " range [" << range_min << " - " << range_max << "] initialized\n";
                }
            }

            /**
             * @brief Create vector, and set name of all threads 
             */
            void create_threads() {
                std::cout << " Creating Threads\n";
                for (auto& c : vquick_sort) {
                    c->create();
                    // std::cout << "  " << c->get_name() << " tid : " << c->get_tid() << " created\n";
                } 
            }

            /**
             * @brief Runs all threads 
             */
            void run_threads() {
                std::cout << " Run Threads\n";
                for (auto& r : vquick_sort) {
                    r->run();
                }
            }

            /**
             * @brief Calculates the total delta time for all threads.
             */
            void statistics() {
                std::cout << " Statistics\n";
                std::chrono::microseconds max_delta_ms = std::chrono::microseconds::zero();
                std::chrono::microseconds min_delta_ms = std::chrono::microseconds::zero();
                std::string min_name_thread;
                std::string max_name_thread;
                int cnt_thread = 0;
                for ( auto& d : vquick_sort ) {
                    std::cout << "  " << d->get_name() << " delta time [millisec] : " << ( static_cast<double>( d->delta_time_ms.count() ) / 1000.0 ) << "\n"; 
                    if ( max_delta_ms < d->delta_time_ms ) {
                        max_delta_ms = d->delta_time_ms;
                        max_name_thread = d->get_name();
                    }

                    if ( cnt_thread == 0 ) {
                        min_delta_ms  = d->delta_time_ms;
                        min_name_thread = d->get_name();
                        cnt_thread++; 
                    }
                    else {
                        if ( min_delta_ms > d->delta_time_ms ) {
                            min_delta_ms  = d->delta_time_ms;
                            min_name_thread = d->get_name();
                        }
                    }
                }
                std::cout << "  Max Delta time " << max_name_thread << " [millisec] : " << ( static_cast<double>(max_delta_ms.count()) / 1000.0 ) << "\n"; 
                std::cout << "  Min Delta time " << min_name_thread << " [millisec] : " << ( static_cast<double>(min_delta_ms.count()) / 1000.0 ) << "\n"; 
            }
            
            /**
             * @brief Check the all threads executed.
             */
            void check_all_threads_executed() {
                std::cout << " Check all threads executed\n";
                bool bcheck_all_threads_executed = false;
                while ( !bcheck_all_threads_executed ) {
                    bcheck_all_threads_executed = true;
                    for ( auto& e : vquick_sort ) {
                        if ( e->get_loop_cnt() != 1 ) {
                            bcheck_all_threads_executed = false;
                            break;
                        }
                    } 
                } 
                std::cout << " All threads executed\n";
            }
            
            /**
             * @brief
             */
            void destroy_threads() {
                std::cout << " Destroying threads\n";
                for ( auto& d : vquick_sort ) {
                    // std::cout << "  " << d->get_name() << " ... ";
                    d->destroy();
                    // std::cout << "destroyed\n";
                }
            }

    };

    void main_quick_sort();
    void main_quick_sort() {

        std::cout << "\n BEGIN -- Example Quick Sort --\n";

        c_manager_quick_sort oquick_sort;
        size_t vector_size = 1ULL << 16;
        int min_value = 3;
        int max_value = 10000000;
        int num_of_threads = 1ULL;

        oquick_sort.sort_vector(vector_size,
                                    min_value,
                                    max_value,
                                    num_of_threads);

        std::cout << "\n";
        num_of_threads = 1ULL << 4;
        oquick_sort.sort_vector(vector_size,
                                    min_value,
                                    max_value,
                                    num_of_threads);

        std::cout << "\n END -- Example Quick Sort --\n";
    }
} // ns_test_sort

