# 🎭 ROBO-ACTOR — Session Boot File

Welcome back! Read this file at the start of every Claude Desktop brainstorming session.

---

## Project Summary

**Robo-Actor** is an animatronic Henson-style puppet inspired by Dozer from Fraggle Rock, standing 20–25cm tall. The project combines physical puppet construction, embedded electronics, and custom software into a complete performer system.

### The Three Pillars
1. **The Puppet** — A Dozer-inspired character with servo-driven movement
2. **The Timeline Tool** — Desktop software to author lip-sync and movement sequences from audio
3. **The Controller App** — A touch-based PWA to perform the puppet live

---

## Owner Context
- **Location:** Netherlands 🇳🇱
- **Currency:** € (Euro)
- **Measurements:** Metric (mm, cm, g, kg)
- **Fasteners:** Metric (M2, M3, M4 etc.)
- **Power standard:** 230V mains / EU plugs
- **Preferred suppliers:** Tinytronics (NL), Kiwi Electronics (NL), Reichelt (DE), Conrad (NL), AliExpress EU warehouses
- **Experience level:** Beginner (electronics, mechatronics, programming)
- **Fabrication:** FDM 3D printing (primary), foam + fleece (soft surfaces)

---

## Movement Specification
| Joint | Axes | Servo Count |
|-------|------|------------|
| Head pan (left/right) | 1 | 1 |
| Head tilt (up/down) | 1 | 1 |
| Head roll (side lean) | 1 | 1 |
| Waist | 1 | 1 |
| Mouth open/close | 1 | 1 |
| **Total** | **5** | **5** |

---

## Agreed Technical Decisions

### Hardware Stack
- **Microcontroller:** DFRobot FireBeetle 2 ESP32-E (USB-C, pre-soldered headers, compact 25.4×60mm)
- **Servo driver:** PCA9685 I2C board (16 channels, clean wiring)
- **Servos:** MG90S mini servo (metal gears — upgrade from SG90)
- **Power (prototype):** USB-C power bank at 5V (separate servo + logic rails)
- **Stage 1 actual parts cost:** €38.00 incl. VAT + shipping (see `expenses.md`)
- **Connection:** Wired prototype via hollow left foot cable conduit; bolt/nut mount on right foot

### Key Hardware Notes
- FireBeetle I2C: SDA=GPIO21, SCL=GPIO22 (ESP32 defaults — matches Stage 1 brief)
- FireBeetle uses **USB-C** for programming and power
- MG90S plugs directly into PCA9685 servo headers (standard 3-pin connector)
- PCA9685 I2C address: 0x40 (default)

### Physical Construction
- **Primary structure:** FDM 3D printed (PLA or PETG)
- **Soft surfaces:** Foam + fleece for cheeks and character skin areas
- **Head mechanism:** Sequential axis stack (pan at neck, tilt above, roll above that)
- **Jaw:** Printed jaw on piano wire hinge, pulled by servo inside skull
- **Target height:** 20–25cm total

### Software Stack
- **Firmware:** Arduino/ESP32 (accepts JSON servo commands over Serial/WebSocket)
- **Lip-sync tool:** Python desktop app using `librosa` for audio analysis
- **Timeline tool:** Desktop app (platform TBD in brainstorm) for authoring sequences
- **Controller app:** Progressive Web App (PWA) using WebSockets, low-latency
- **Sync data format:** JSON keyframe format (to be defined in session)

---

## Prototype Order (agreed)
1. **Stage 1 — Electronics chain:** ESP32 + PCA9685 + 1× MG90S servo sweeping. First Claude Code task. ⏳ Hardware ordered.
2. **Stage 2 — Mouth mechanism:** Minimal jaw test rig. One servo, hinged jaw, linkage.
3. **Stage 3 — Single head axis:** Pan servo mounted and moving. Understand torque and range.
4. **Stage 4 — Waist joint:** Simplest joint. Add after head axis is understood.
5. **Stage 5 — Full integration:** All 5 servos running simultaneously.

---

## The Virtual Team

| Name | Role | File |
|------|------|------|
| 🎭 Pippa — Puppeteer & Performance Consultant | Expressiveness, performance, illusion of life | `team/pippa-puppeteer-and-performance-consultant.md` |
| ⚡ Eli — Electrical Engineer | Circuits, power, components, wiring safety | `team/eli-electrical-engineer.md` |
| 🤖 Roz — Roboticist & Mechatronics Engineer | System integration, joints, servo mechanics | `team/roz-roboticist-and-mechatronics-engineer.md` |
| 💻 Ada — Embedded Systems & Firmware Developer | ESP32 firmware, servo control, protocols | `team/ada-embedded-systems-and-firmware-developer.md` |
| 🔊 Sam — Audio & DSP Engineer | Lip-sync pipeline, audio analysis, phonemes | `team/sam-audio-and-dsp-engineer.md` |
| 🏗️ Felix — Mechanical Design & CAD Engineer | 3D printable parts, joints, FDM constraints | `team/felix-mechanical-design-and-cad-engineer.md` |
| 📱 Maya — UX & Mobile App Developer | Touch controller PWA, latency, performer UX | `team/maya-ux-and-mobile-app-developer.md` |

---

## Session Rules

### Claude Desktop (YOU ARE HERE)
- **Brainstorming and design decisions only**
- Read issues to catch up on progress
- End every session with a clear brief for Claude Code
- Do NOT commit code or files to the repository (except boot.md and team files during setup)

### Claude Code
- **All coding, file creation, and git commits**
- Receives briefs from Desktop sessions
- Logs completion back to GitHub Issues

---

## How to Start a Session

1. Ask Claude Desktop: *"Please read boot.md and the open GitHub issues, then summarise where we are."*
2. Claude will read this file and check `https://github.com/snottleDev/robo-actor/issues`
3. Pick up where you left off or start a new topic

---

## GitHub Issues Log

All session summaries and Claude Code briefs are logged as GitHub Issues.

- Browse issues at: `https://github.com/snottleDev/robo-actor/issues`
- Completed work is closed with a summary comment
- Open issues represent active or upcoming work

---

## Project Status

| Component | Status |
|-----------|--------|
| Repository setup | ✅ Complete |
| Virtual team created | ✅ Complete |
| Hardware stack decided | ✅ Complete (FireBeetle ESP32-E + PCA9685 + MG90S) |
| Stage 1 hardware purchased | ✅ Ordered from TinyTronics — €38.00 |
| Expense tracking | ✅ Active — see `expenses.md` |
| Mechanical concept | ✅ Agreed in principle |
| Prototype order defined | ✅ Complete (5 stages) |
| Stage 1 firmware | ⏳ Awaiting hardware delivery |
| CAD / printable parts | 🔲 Not started |
| Lip-sync tool | 🔲 Not started |
| Timeline tool | 🔲 Not started |
| Controller PWA | 🔲 Not started |

---

*Last updated: Session 2 — Stage 1 hardware purchased, FireBeetle ESP32-E confirmed, MG90S selected, expense tracking started*
