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
- **Microcontroller:** ESP32 (WiFi built-in for future wireless; USB serial for wired prototype)
- **Servo driver:** PCA9685 I2C board (16 channels, clean wiring)
- **Servos:** SG90 / MG90S class micro servos
- **Power (prototype):** USB-C power bank at 5V (separate servo + logic rails)
- **Connection:** Wired prototype via hollow left foot cable conduit; bolt/nut mount on right foot

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

## The Virtual Team

| Name | Role | File |
|------|------|------|
| 🎭 Pippa | Puppeteer & Performance | `team/pippa-the-puppeteer.md` |
| ⚡ Eli | Electrical Engineer | `team/eli-the-electrical-engineer.md` |
| 🤖 Roz | Roboticist & Mechatronics | `team/roz-the-roboticist.md` |
| 💻 Ada | Embedded Developer | `team/ada-the-embedded-developer.md` |
| 🔊 Sam | Audio & DSP Engineer | `team/sam-the-audio-engineer.md` |
| 🏗️ Felix | CAD & Mechanical Design | `team/felix-the-cad-engineer.md` |
| 📱 Maya | UX & App Developer | `team/maya-the-app-developer.md` |

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
| Hardware stack decided | ✅ Complete (ESP32 + PCA9685) |
| Mechanical concept | ✅ Agreed in principle |
| CAD / printable parts | 🔲 Not started |
| Firmware (servo control) | 🔲 Not started |
| Lip-sync tool | 🔲 Not started |
| Timeline tool | 🔲 Not started |
| Controller PWA | 🔲 Not started |

---

*Last updated: Session 1 — Project setup and initial hardware decisions*
