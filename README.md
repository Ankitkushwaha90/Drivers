```mdx
---
title: "Keyword Driver Framework in Python"
description: "A detailed guide on implementing a keyword-driven test automation framework in Python."
---

## Introduction

A **keyword driver** is a concept often used in automation frameworks, particularly in test automation. It is a scripting approach where test cases are written using keywords that represent actions or functions. These keywords are then mapped to specific functions or methods in the code, making test cases more readable and modular.

## Example: Keyword Driver Framework in Python

### Step 1: Define the Keywords (Actions) as Functions

```python
# Keyword Driver Framework

def open_browser(browser="chrome"):
    print(f"Opening {browser} browser")

def navigate_to_url(url):
    print(f"Navigating to URL: {url}")

def enter_text(locator, text):
    print(f"Entering text '{text}' into element with locator: {locator}")

def click_element(locator):
    print(f"Clicking element with locator: {locator}")

def close_browser():
    print("Closing the browser")
```

### Step 2: Create a Mapping of Keywords to Functions

```python
keyword_map = {
    "open_browser": open_browser,
    "navigate_to_url": navigate_to_url,
    "enter_text": enter_text,
    "click_element": click_element,
    "close_browser": close_browser,
}
```

### Step 3: Define Test Cases Using Keywords

```python
test_case_1 = [
    ("open_browser", {"browser": "chrome"}),
    ("navigate_to_url", {"url": "https://example.com"}),
    ("enter_text", {"locator": "username_field", "text": "testuser"}),
    ("enter_text", {"locator": "password_field", "text": "testpass"}),
    ("click_element", {"locator": "login_button"}),
    ("close_browser", {}),
]
```

### Step 4: Execute the Test Case Using the Keyword Driver

```python
def execute_test_case(test_case):
    for keyword, arguments in test_case:
        if keyword in keyword_map:
            keyword_map[keyword](**arguments)
        else:
            print(f"Keyword '{keyword}' not found in keyword map!")
```

### Step 5: Run the Test Case

```python
execute_test_case(test_case_1)
```

## Explanation of the Code

### 1. Keywords as Functions
Each keyword represents an action, such as:
- **`open_browser`**: Opens a browser.
- **`navigate_to_url`**: Navigates to a specific URL.
- **`enter_text`**: Enters text into a field.
- **`click_element`**: Clicks an element.
- **`close_browser`**: Closes the browser.

### 2. Keyword Mapping
A dictionary (`keyword_map`) is used to map keyword names (strings) to their corresponding functions.

### 3. Test Case Definition
Test cases are defined as a list of tuples containing:
- A keyword (string).
- A dictionary of arguments to pass to the function.

### 4. Test Case Execution
The `execute_test_case` function:
- Looks up the keyword in the `keyword_map`.
- Calls the corresponding function with provided arguments.

### 5. Expected Output

```shell
Opening chrome browser
Navigating to URL: https://example.com
Entering text 'testuser' into element with locator: username_field
Entering text 'testpass' into element with locator: password_field
Clicking element with locator: login_button
Closing the browser
```

## Advantages of the Keyword Driver Framework

- **Modularity**: Reusable actions.
- **Readability**: Easy to understand test cases.
- **Scalability**: New keywords can be added without changing execution logic.
- **Separation of Concerns**: Test logic is separate from implementation.

## Real-World Use Case with Selenium Integration

This framework can be extended for real web automation using Selenium:

```python
from selenium import webdriver

def open_browser(browser="chrome"):
    if browser == "chrome":
        driver = webdriver.Chrome()
    elif browser == "firefox":
        driver = webdriver.Firefox()
    return driver

def navigate_to_url(driver, url):
    driver.get(url)

def enter_text(driver, locator, text):
    driver.find_element(*locator).send_keys(text)

def click_element(driver, locator):
    driver.find_element(*locator).click()

def close_browser(driver):
    driver.quit()

keyword_map = {
    "open_browser": open_browser,
    "navigate_to_url": navigate_to_url,
    "enter_text": enter_text,
    "click_element": click_element,
    "close_browser": close_browser,
}

def execute_test_case(test_case):
    driver = None
    for keyword, arguments in test_case:
        if keyword in keyword_map:
            if keyword == "open_browser":
                driver = keyword_map[keyword](**arguments)
            else:
                keyword_map[keyword](driver, **arguments)
        else:
            print(f"Keyword '{keyword}' not found in keyword map!")
```

## Conclusion

A **Keyword Driver Framework** improves test automation by making it:
- **Readable**: Test cases are written in a human-readable format.
- **Reusable**: The same keywords can be used in multiple test cases.
- **Scalable**: New keywords can be added easily.
- **Maintainable**: Changing a keyword implementation updates all test cases using it.

This approach is widely used in automation tools like **Selenium** and **Appium**. Let me know if you need further clarifications! 🚀
```
