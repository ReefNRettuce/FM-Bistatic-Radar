# 2025-10-10T15:48:01.276622600
import vitis

client = vitis.create_client()
client.set_workspace(path="FM-Bistatic-Radar")

comp = client.create_hls_component(name = "joint_process_estimator_v2",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

vitis.dispose()

