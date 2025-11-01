# 2025-10-28T20:26:48.507909
import vitis

client = vitis.create_client()
client.set_workspace(path="FM-Bistatic-Radar")

comp = client.create_hls_component(name = "NLMS_filter",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

vitis.dispose()

vitis.dispose()

