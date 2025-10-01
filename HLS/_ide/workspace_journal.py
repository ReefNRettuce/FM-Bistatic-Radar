# 2025-09-30T20:57:38.663719700
import vitis

client = vitis.create_client()
client.set_workspace(path="HLS")

vitis.dispose()

