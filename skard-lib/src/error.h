/**
 * @file
 *
 * @brief Error handling
 */

#ifndef CSKARD_ERROR_H
#define CSKARD_ERROR_H

/**
 * @defgroup EXIT_CODES EXIT CODES
 *
 * @brief All exit codes
 *
 * @todo Start following common standard for exit codes
 * @{
 */

/**
 * @brief Successful exit status of the program.
 */
#define CSKARD_EXIT_SUCCESS 0

/**
 * @brief Failure exit status of the program with unspecified error.
 *
 * @note This should not be used if more appropriate exit code exists.
 */
#define CSKARD_EXIT_FAILURE_UNSPECIFIED 1

/**
 * @brief Failure exit status of the program when the command was used incorrectly.
 */
#define CSKARD_EXIT_WRONG_USAGE 2

/**
 * @brief Failure exit status of the program when the system is out of memory.
 */
#define CSKARD_EXIT_OUT_OF_MEMORY 3

/**
 * @}
 */

/**
 * @brief Prints error message.
 *
 * @param message error message
 */
void printError(const char* message);

/**
 * @brief Prints error message and exits the program.
 *
 * @param code exit code
 * @param message error message
 */
void exitError(int code, const char* message);

/**
 * @brief Exits with out of memory error message.
 */
void exitOutOfMemory();

#endif //CSKARD_ERROR_H
