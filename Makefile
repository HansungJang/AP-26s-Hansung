.PHONY: clean

# Remove Visual C/C++ build artifacts from this directory and its subdirectories.
clean:
	powershell -NoProfile -Command "Get-ChildItem -LiteralPath '$(CURDIR)' -Recurse -File | Where-Object { @('.exe', '.ilk', '.obj', '.pdb') -contains $$_.Extension.ToLowerInvariant() } | Remove-Item -Force"