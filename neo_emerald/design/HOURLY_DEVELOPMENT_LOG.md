# Hourly development log

## 2026-11-27 23:43 CST — Mossdeep evacuation
- Baseline: 77dfe49b3fcdd1906913584355c1156c37a7976b; newer Dewford welfare checks preserved.
- Build: bc84f2f8 requires ferry crew interaction; 4314498d removes forced city warp and directs player east to waterfront. Rescuees are removed from landing and existing state-4 transition shows them at quay. This is independent rendezvous, not a following-NPC escort.
- Refine: 3c379751 adds regression guards; seven equivalent source assertions executed against fetched scripts and passed. Existing state-5 reward ordering preserved. No IDs or art changed.
- Polish: clear destination and interaction dialogue. Full Python suite, collision, boarding movement, compilation and emulator unverified. Existing saves at state 4 can speak to crew; state 5 remains completed.
- CI: baseline PR-triggered workflow query empty; no build triggered manually.
- Next: verify connected walking route and boarding movement, then university encounter/warp blockers. Preserve Badge 2 release boundary and Cayton milestone v2.
