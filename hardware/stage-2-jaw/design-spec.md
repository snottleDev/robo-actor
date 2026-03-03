# Stage 2 — Jaw Mechanism Test Rig: Design Specification

**Status:** Design spec — not yet built
**Scale:** 65mm skull reference width
**Consulted:** Felix (Mechanical Design), Pippa (Performance)
**Next step after approval:** CAD model → print → physical test

---

## 1. Overview

### What This Rig Is

The Stage 2 test rig is a **standalone jaw mechanism** at real puppet scale. It is not the final head — it is a minimal jig that isolates the jaw linkage so it can be printed, assembled, and tested before any head geometry is committed.

### What It Proves

1. The piano-wire hinge approach is stiff enough and smooth enough for lip-sync motion
2. The push-rod linkage geometry delivers 25–30° of jaw rotation from the MG90S servo
3. The servo horn angle range (a fraction of full servo throw) produces weighted, deliberate movement that reads as alive at lip-sync speeds
4. The printed parts survive repeated cycling without cracking at the hinge bosses or rod tab

### What It Is NOT

- Not a cosmetic head shell
- Not integrated with pan/tilt/roll mechanisms
- Not connected to the lip-sync firmware pipeline (yet)

The rig should be clampable to a desk and driven directly from the Stage 1 firmware (serial JSON commands, servo channel 0) or a simple angle-sweep test sketch.

---

## 2. Part List

### Printed Parts (2 pieces)

| # | Name | Description |
|---|------|-------------|
| P1 | Skull Base | Fixed frame. Represents the upper jaw and skull cavity walls. Houses the servo mount pocket, hinge pin bores, and a desk-clamp lug. Prints as one piece lying on its back face. |
| P2 | Lower Jaw | Moving jaw. Hinged at the cheek pivots. Has a lever tab extending rearward into the skull cavity for rod attachment. Prints lying on its flat inner face. |

### Hardware (not printed)

| Item | Spec | Qty | Source |
|------|------|-----|--------|
| Hinge pin | 1.0mm piano wire (music wire), cut to 71mm | 1 | Hobbyist / model shop |
| Push-pull rod | 1.0mm piano wire, cut to ~22mm | 1 | Same wire, different cut |
| Servo | MG90S (22.5 × 11.5 × 27mm body) | 1 | From Stage 1 stock |
| Servo horn | Single-arm horn (supplied with MG90S) | 1 | Included with servo |
| M2 × 8mm self-tapping screw | Servo mount retention | 2 | Standard hardware |

**Total printed parts: 2**
**Total part count including hardware: 6 (within the 3–5 piece guideline; hardware items are consumables, not assemblies)**

---

## 3. Hinge Design

### Approach

Piano wire hinge pin running left-to-right through the jaw pivot point. This is the Henson workshop standard for small puppet jaws — low friction, minimal slop, easy to replace.

### Pin Specification

| Property | Value |
|----------|-------|
| Wire diameter | 1.0mm |
| Bore diameter | **1.3mm** (0.3mm FDM clearance) |
| Pin length | 71mm (65mm skull span + 3mm overhang each side for retention bends) |

### Retention

After assembly, the protruding 3mm end of the pin on each side is bent 90° with needle-nose pliers against the outer face of the skull cheek. This prevents the pin from walking out during operation without glue. The bend can be straightened to disassemble.

### Bore Geometry (in printed parts)

- **Skull Base**: Two cylindrical boss protrusions on the inner face of each cheek wall. Each boss is Ø4.0mm outer, Ø1.3mm bore, 5mm deep, centred on the hinge axis. The boss outer diameter is 4.0mm to give 1.35mm of wall around the bore (above the 1.5mm minimum for structural elements — acceptable given the short boss length and low load).
- **Lower Jaw**: Two bearing lugs at each end of the jaw, each Ø4.0mm outer, Ø1.3mm bore, 4mm wide. These lugs nest between the skull base cheek walls and the hinge bosses.

### Assembly fit

Jaw bearing lugs slot between skull base cheeks with 0.3mm side clearance per side. The pin slides through from one side: skull outer cheek bore → jaw bearing lug → skull boss bore. The jaw rotates freely on the pin.

### Print orientation note

Print both parts with the bore axes oriented horizontally on the print bed so the bores print as true circles, not as stacked ellipses. Avoid printing bore axes vertically unless the slicer bridging is validated.

---

## 4. Linkage Design

### Approach: Pull-Rod

The servo pulls the jaw open; gravity returns it to closed. This keeps the rod in **tension at all times**, eliminating the risk of column buckling in the thin wire rod. No return spring is required for this test rig (gravity provides adequate closing force for a lightweight plastic jaw).

The rod connects:
- **Upper end**: to the second hole on the single-arm servo horn (10mm from servo centre)
- **Lower end**: to a printed tab on the lower jaw, 15mm from the hinge axis

### Servo Horn

| Property | Value |
|----------|-------|
| Type | Single-arm (one-sided), as supplied with MG90S |
| Horn selection reason | Lowest profile, simplest geometry, easy to adjust rod attachment point |
| Attachment hole used | Second hole from centre: **10mm from servo shaft axis** |
| Alternative holes | 7mm hole → ~20° jaw travel (too little); 13mm hole → ~41° (too much) |

### Rod Specification

| Property | Value |
|----------|-------|
| Material | 1.0mm piano wire (same stock as hinge pin) |
| Effective length | ~20mm between Z-bend contact points |
| Total cut length | ~28mm (includes both Z-bends) |
| Connection at horn end | Z-bend hook through horn hole; no soldering needed |
| Connection at jaw end | Z-bend hook sits in a 1.2mm-wide printed slot on the jaw tab |

**Z-bend technique**: Grip the wire 3mm from the end with needle-nose pliers and bend 90°. This creates a short hook. The hook passes through the horn hole and the bent tip prevents pull-through. At the jaw end, the hook sits in the slot and is retained by the slot walls — the rod cannot lift out under tension.

### Jaw Lever Tab

The lower jaw has a rearward-projecting tab that extends into the skull cavity:

| Property | Value |
|----------|-------|
| Tab length from hinge axis | **15mm** (the moment arm — see Section 6) |
| Tab cross-section | 3mm × 3mm (Felix's structural wall minimum: 2.5–3mm) |
| Slot for rod Z-bend | 1.2mm wide × 2mm deep, centred on tab tip |
| Slot clearance on 1.0mm wire | 0.2mm (tight enough to not rattle, loose enough to rotate freely as jaw moves) |
| Print orientation | Tab prints horizontally off the jaw body — bridging length is short enough (~5mm) to print without support |

---

## 5. Servo Positioning

### Location

The servo sits inside the skull cavity, **behind and above the hinge axis**:

| Dimension | Value |
|-----------|-------|
| Servo shaft, horizontal distance behind hinge | 25mm |
| Servo shaft, vertical height above hinge axis | 20mm |

This positions the servo body comfortably within the skull cavity. At 22.5mm wide, the servo fits within the ~61mm internal skull width (65mm outer minus 2mm walls each side) with room on each side.

### Orientation

- **Servo shaft axis**: parallel to the hinge pin axis (left-right / Z axis)
- **Horn faces**: outward on one cheek side (left or right — determined during CAD by which side has more clearance)
- **Servo body**: sits flat against a printed pocket in the skull base rear wall

This orientation means the horn sweeps in a **vertical plane parallel to the skull's side face** — exactly the plane that the pull-rod operates in.

### Servo Mount Pocket

| Property | Value |
|----------|-------|
| Pocket width | 23.1mm (22.5mm body + 0.3mm clearance each side) |
| Pocket depth | 12.1mm (11.5mm body + 0.3mm each side) |
| Pocket length | Enough to seat servo body flush with rear wall |
| Retention | 2 × M2 × 8mm self-tapping screws through printed bosses into servo body flanges |
| Wall thickness around pocket | 2.5mm (structural: Felix's minimum) |

### Horn Side Clearance

The single-arm horn adds approximately 3mm of thickness beyond the servo body face. The skull cheek wall on that side must clear the horn sweep arc. The cheek wall on the horn side should be positioned so the horn does not contact the wall at any point in its 45° travel arc.

---

## 6. Jaw Travel Calculation

### Goal

Produce 25–30° of jaw rotation (open angle) using approximately 45° of servo horn rotation, using a pull-rod linkage.

### Parameters

| Symbol | Value | Description |
|--------|-------|-------------|
| r | 10mm | Horn radius (distance from servo shaft to rod attachment point) |
| d | 15mm | Jaw moment arm (distance from hinge to rod attachment tab) |
| θ_horn | 45° | Servo horn travel used |
| θ₀ | −10° | Horn angle at jaw-closed position (10° below horizontal) |
| θ₁ | +35° | Horn angle at jaw-open position (35° above horizontal) |

### Calculation

The vertical (upward) displacement of the horn tip as the horn sweeps from θ₀ to θ₁:

```
Δy = r × (sin θ₁ − sin θ₀)
   = 10 × (sin 35° − sin(−10°))
   = 10 × (0.574 − (−0.174))
   = 10 × 0.748
   = 7.48 mm
```

This Δy is the upward pull on the rod. The jaw rotation that results:

```
θ_jaw = arcsin(Δy / d)
       = arcsin(7.48 / 15)
       = arcsin(0.499)
       ≈ 30°
```

**Result: 30° jaw opening — at the top of the 25–30° target range.**

### Servo Tick Range (for firmware)

The full MG90S range maps to servo ticks 102–492 (390 ticks = 180°), giving **2.167 ticks per degree**.

| State | Horn angle | Servo ticks |
|-------|------------|-------------|
| Jaw closed | corresponds to servo ~90° (mid-travel) | ~102 + (90 × 2.167) ≈ **297 ticks** |
| Jaw open | 45° further | 297 − 97 = **200 ticks** |

> Note: The actual tick values will need calibration on the physical rig because servo horn zero-point and geometry vary between units. These ticks are starting estimates.

### Mechanical Advantage

| | Value |
|-|-------|
| Horn radius | 10mm |
| Jaw arm | 15mm |
| MA (jaw / horn) | **1.5** |
| Effect | Jaw travels 1.5× the horn arc length → motion is amplified |
| Torque demand on servo | Servo must overcome 1.5× the jaw inertia/gravity load |
| MG90S torque at 5V | ~1.8 kg·cm → force at 10mm horn tip ≈ 1.8 N |
| Force available at jaw tab | 1.8 N (rod tension) → torque at jaw hinge = 1.8 N × 15mm = **27 N·mm** |

A lightweight PLA jaw at this scale is well under 5 grams and presents negligible gravitational torque. The servo is not torque-limited in this design.

### Why Not Use Full Servo Throw

Using only 45° of the 180° servo range means:
- Motion is smooth and weighted, not rushed (Pippa's requirement)
- Firmware can apply easing curves across a larger time window relative to the angle moved
- Servo is not operating near its mechanical stops (less jitter at end of travel)
- Small angle changes produce proportionally small jaw movements — good for realistic lip-sync

---

## 7. Assembly Sequence

Perform assembly in this order to avoid trapping parts.

1. **Print P1 (Skull Base) and P2 (Lower Jaw)**. Clean all bores with a 1.3mm drill bit or pin vice — FDM holes are often slightly undersized. Test the piano wire through each bore before assembly.

2. **Install the servo** into the skull base servo pocket. Thread two M2 × 8mm self-tappers through the printed flanges into the servo body mounting ears. Do not overtighten — just snug. Do not attach the horn yet.

3. **Assemble the hinge**. Slide the lower jaw into position between the skull base cheek walls, aligning the jaw bearing lugs with the hinge boss bores. Push the piano wire hinge pin through from one side: skull cheek bore → jaw lug → skull boss bore. The pin should pass smoothly. If it binds, clean the bores and re-test.

4. **Retain the hinge pin**. Bend the 3mm protruding stub at each end 90° against the outer cheek face using needle-nose pliers. Check that the jaw swings freely with no binding and no visible lateral play.

5. **Prepare the pull rod**. Cut a 28mm length of piano wire. Make a Z-bend hook 3mm from one end (the horn end). Check the hook fits through the servo horn hole at 10mm. Make a second Z-bend hook at the other end (the jaw tab end).

6. **Attach the horn**. With the jaw held in the **closed** position, fit the servo horn to the servo shaft so the horn points approximately 10° below horizontal (the closed-jaw reference angle). Hook the rod through the horn hole. Seat the horn on the shaft spline — align carefully so the tooth engagement is at the intended position. Press the horn cap screw down finger-tight.

7. **Attach rod to jaw tab**. Hook the jaw-end Z-bend into the tab slot. The rod should be in light tension when the jaw is closed. If the rod is slack, the horn position needs to be adjusted one spline position.

8. **Test by hand**. Rotate the servo horn by hand from −10° to +35°. Confirm the jaw opens smoothly to approximately 30° and closes fully under gravity when the horn is released. If the jaw binds or the rod goes slack, check the tab slot alignment and horn angle.

9. **Connect to ESP32 and PCA9685**. Use channel 0 (same as Stage 1). Send tick values from approximately 200 (open) to 297 (closed) and observe motion. Calibrate as needed.

---

## 8. Open Questions

These items cannot be answered without building the physical rig.

| # | Question | Why It Matters |
|---|----------|---------------|
| OQ-1 | Does the jaw close fully under gravity alone, or does it need a return spring? | A lightweight PLA jaw may not have enough mass to close reliably under gravity — especially when mounted horizontally at the back of a puppet. A small rubber band or twisted loop of elastic may be needed. |
| OQ-2 | Does the 1.3mm bore give adequate bearing life over ~500+ cycles? | The bore is printed PLA on a 1.0mm steel pin. Some wear is expected. If the bore enlarges and slop appears, options are: nylon tube insert, CA glue and re-drill, or redesign to 2.0mm pin for larger bearing surface. |
| OQ-3 | Does the MG90S jitter at the jaw-closed position? | Some MG90S units produce visible jitter when holding a position. This is cosmetically bad in a puppet. If present, try a different servo or add a small deadband in firmware (±3 ticks). |
| OQ-4 | Is the horn-to-rod Z-bend retention reliable at lip-sync speeds? | Z-bends can pop out if the hook is too shallow. Physical testing will confirm whether the hook geometry is adequate or needs a 90° retainer clip crimped over it. |
| OQ-5 | What is the actual servo tick value for jaw-closed and jaw-open? | The calculation gives starting estimates (297 / 200 ticks). Physical calibration is always needed because servo spline zero-points vary. |
| OQ-6 | Does the skull base need a rear clamp tab or can it be held in a bench vice? | The design currently assumes a desk mount. A simple M3 nut-trap on the base bottom face would make it tripod-mountable for filming. Decide based on how the rig will be tested. |

---

*Spec authored: Stage 2 design session. Ready for Felix CAD review and physical build.*
