---
tags:
  - cs/os
  - algorithms/rng
  - project/specs
created: 2025-12-16
sticker: ""
---

# Linear Congruential Generator (LCG) – Design and Implementation Notes

## 1. What is a Linear Congruential Generator (LCG)?

A **Linear Congruential Generator (LCG)** is a simple and well-known pseudo-random number generator defined by the recurrence relation:

$$
X_{n+1} = (a X_n + c) \bmod m
$$

**Where:**
* $X_n$ is the current state
* $a$ is the multiplier
* $c$ is the increment
* $m$ is the modulus

The generator produces a deterministic sequence of integers in the range:
$$
0 \le X_n < m
$$

Despite its simplicity, an LCG can produce high-quality pseudo-random sequences when its parameters are chosen carefully.

---

## 2. Design Goals for This Project

> [!GOAL] Project Priorities
> This implementation is intended for **operating-system-level use**, where the priorities are:

* Predictable and reproducible behavior
* Acceptable statistical quality
* No obvious patterns in low-order bits
* Clear mathematical guarantees
* Simplicity and ease of reasoning
* **Note:** Cryptographic security is *not* a goal.

---

## 3. Choice of Modulus

**Selected Modulus:**
$$
m = 2^{31} - 1
$$

This value is a **Mersenne prime**, which provides strong mathematical properties.

**Rationale:**
* Prime modulus avoids low-bit correlation issues common with $m = 2^k$.
* Produces a long period and better uniformity.
* Historically used in well-known generators (e.g., Park–Miller).
* Suitable for OS simulations, scheduling, and randomized policies.
* *This choice prioritizes randomness quality over raw speed, which is appropriate for OS-level code.*

---

## 4. Choice of Increment

**Selected Increment:**
$$
c = 0
$$

This results in a **Multiplicative LCG**:
$$
X_{n+1} = (a X_n) \bmod m
$$

**Rationale:**
* With a prime modulus, an increment is not required for good behavior.
* Simplifies the implementation.
* Reduces arithmetic operations.
* Easier to reason about mathematically.

---

## 5. Choice of Multiplier

**Selected Multiplier:**
$$
a = 16807
$$

**Rationale:**
* This value is known as the **Park–Miller multiplier**.
* Proven to produce a full-period generator when used with $m = 2^{31} - 1$.
* Well-studied and widely referenced in academic literature.
* Produces a period of $m - 1$, which is sufficient for this project.
* *This choice avoids experimental or ad-hoc parameter selection.*

---

## 6. Seed Handling

**Constraint:**
$$
X_0 \neq 0
$$

**Rationale:**
* In a multiplicative LCG, a seed of zero results in a constant zero sequence.
* The implementation enforces a non-zero seed.
* If a zero seed is provided, it is replaced with a valid default value.
* This guarantees correct generator behavior.

---

## 7. Period Behavior and Testing

**Expected Period:**
With the chosen parameters:
1.  **Modulus:** $2^{31} - 1$
2.  **Multiplier:** $16807$
3.  **Increment:** $0$

The generator has a **maximum period** of $m - 1$.

**Test Strategy:**
A simple test is performed to:
- Generate a sequence of values.
- Ensure no early repetition occurs.
- Verify that the state remains within bounds.
- Observe distribution and absence of short cycles.

This confirms correct implementation of the recurrence relation.

---

## 8. Summary of Design Decisions

> [!SUMMARY] Configuration Table
>
| Component | Choice | Reason |
| :--- | :--- | :--- |
| **Generator Type** | Multiplicative LCG | Simple, proven, well-understood |
| **Modulus** | $2^{31} - 1$ | Prime, good statistical properties |
| **Multiplier** | $16807$ | Known good parameter (Park-Miller) |
| **Increment** | $0$ | Simplifies design |
| **Seed** | Non-zero enforced | Prevents degenerate behavior |

## 9. Conclusion

This LCG implementation is designed as a reliable, mathematically sound pseudo-random number generator suitable for operating-system-level experimentation and simulation. The design favors clarity, correctness, and reproducibility, aligning with classic systems engineering principles.