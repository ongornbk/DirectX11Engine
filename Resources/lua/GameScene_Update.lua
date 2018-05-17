if IsKeyHit(1) == true then PostQuitMessage(1) end
if IsKeyHit(2) == true then PlayMusic("Solitaire") end
if IsKeyHit(3) == true then PlayMusic("harrogath") end
if IsKeyHit(4) == true then PlayMusic("ph1") end
if IsKeyHit(5) == true then SetRendereringStyle(0) end
if IsKeyHit(6) == true then SetRendereringStyle(1) end
if GetMouseState(0) == true
then
GetHero()
GetMousePosition()
SetTaskGotoPoint()
end