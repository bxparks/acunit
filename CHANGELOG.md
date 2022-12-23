# Changelog

* Unreleased
* 0.1.0 (2022-12-23)
    * Create `AcuContext` struct to replace global variables
      (`acu_tests_status`, `acu_tests_executed` and `acu_tests_failed`)
        * Rename `acu_tests_status` to `AcuContext.err` and flip meaning of 0
          and 1.
        * Rename `ACU_VARS()` to ACU_CONTEXT()`.
* 0.0.0 (2022-08-22)
    * Create project on GitHub.
    * Upload initial code and documentation.
