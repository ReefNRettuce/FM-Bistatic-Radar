# 2025-11-08T22:00:58.831770700
import vitis

client = vitis.create_client()
client.set_workspace(path="FM-Bistatic-Radar")

vitis.dispose()

comp = client.create_hls_component(name = "gradiant_adaptive_lattice",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

vitis.dispose()

